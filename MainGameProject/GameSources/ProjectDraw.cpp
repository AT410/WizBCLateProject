#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	struct MapTipDraw::Impl
	{
		vector<shared_ptr<TextureResource>> m_textures;

		Impl()
		{

		}
	};

	MapTipDraw::MapTipDraw(const shared_ptr<GameObject>& objptr)
		:SmBaseDraw(objptr)
	{

	}

	MapTipDraw::~MapTipDraw()
	{

	}

	
	void MapTipDraw::OnCreate()
	{

	}

	void MapTipDraw::OnDraw()
	{
		auto mesh = GetMeshResource();
		if (mesh == nullptr)
		{
			throw(BaseException(L"",L"",L""));
		}

		// -- �f�o�C�X�̎擾 --
		auto DeviceRes = App::GetApp()->GetDeviceResources();
		auto pD3Device = DeviceRes->GetD3DDevice();
		auto pD3DeviceContext = DeviceRes->GetD3DDeviceContext();
		auto RenderState = DeviceRes->GetRenderState();

		// -- �V�F�[�_�[���\�[�X --
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };

		// -- �p�����[�^�ݒ� --
		auto ObjectPtr = GetGameObject();

		auto TransComp = ObjectPtr->GetComponent<Transform>();

		auto CameraPtr = ObjectPtr->OnGetDrawCamera();

		// -- �R���X�^���g�o�b�t�@ --
		GameBuffer buffer;
		buffer.World = transpose(TransComp->GetWorldMatrix());
		buffer.View = transpose(CameraPtr->GetViewMatrix());
		buffer.Projection = transpose(CameraPtr->GetProjMatrix());

		//--!���C�g���g�p���Ȃ��̂Őݒ肵�Ȃ�

		// -- Diffuse�EEmissive --
		buffer.Diffuse = GetDiffuse();
		buffer.Emissive = GetEmissive();

		// -- �R���X�^���g�o�b�t�@�̍X�V���� --
		pD3DeviceContext->UpdateSubresource(GBuffer::GetPtr()->GetBuffer(), 0, nullptr, &buffer, 0, 0);

		UINT offset, stride;
		stride = mesh->GetNumStride();
		offset = 0;

		// -- ���_�o�b�t�@�̐ݒ� --
		pD3DeviceContext->IASetVertexBuffers(0, 1, &mesh->GetVertexBuffer(), &stride, &offset);
		// -- �C���f�b�N�X�o�b�t�@��ݒ� --
		pD3DeviceContext->IASetIndexBuffer(mesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
		// -- �`����@ --
		pD3DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// -- ������ --
		float blendfact[4] = { 0.0f };
		pD3DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(),blendfact,D3D11_DEFAULT_SAMPLE_MASK);

		// -- �f�v�X�X�e���V���o�b�t�@ --
		RenderState->SetBlendState(pD3DeviceContext, GetBlendState());
		pD3DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);

		// -- �V�F�[�_�[ --
	}
}