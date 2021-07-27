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

		// -- デバイスの取得 --
		auto DeviceRes = App::GetApp()->GetDeviceResources();
		auto pD3Device = DeviceRes->GetD3DDevice();
		auto pD3DeviceContext = DeviceRes->GetD3DDeviceContext();
		auto RenderState = DeviceRes->GetRenderState();

		// -- シェーダーリソース --
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };

		// -- パラメータ設定 --
		auto ObjectPtr = GetGameObject();

		auto TransComp = ObjectPtr->GetComponent<Transform>();

		auto CameraPtr = ObjectPtr->OnGetDrawCamera();

		// -- コンスタントバッファ --
		GameBuffer buffer;
		buffer.World = transpose(TransComp->GetWorldMatrix());
		buffer.View = transpose(CameraPtr->GetViewMatrix());
		buffer.Projection = transpose(CameraPtr->GetProjMatrix());

		//--!ライトを使用しないので設定しない

		// -- Diffuse・Emissive --
		buffer.Diffuse = GetDiffuse();
		buffer.Emissive = GetEmissive();

		// -- コンスタントバッファの更新処理 --
		pD3DeviceContext->UpdateSubresource(GBuffer::GetPtr()->GetBuffer(), 0, nullptr, &buffer, 0, 0);

		UINT offset, stride;
		stride = mesh->GetNumStride();
		offset = 0;

		// -- 頂点バッファの設定 --
		pD3DeviceContext->IASetVertexBuffers(0, 1, &mesh->GetVertexBuffer(), &stride, &offset);
		// -- インデックスバッファを設定 --
		pD3DeviceContext->IASetIndexBuffer(mesh->GetIndexBuffer().Get(), DXGI_FORMAT_R16_UINT, 0);
		// -- 描画方法 --
		pD3DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// -- 半透明 --
		float blendfact[4] = { 0.0f };
		pD3DeviceContext->OMSetBlendState(RenderState->GetAlphaBlendEx(),blendfact,D3D11_DEFAULT_SAMPLE_MASK);

		// -- デプスステンシルバッファ --
		RenderState->SetBlendState(pD3DeviceContext, GetBlendState());
		pD3DeviceContext->OMSetDepthStencilState(RenderState->GetDepthDefault(), 0);

		// -- シェーダー --
	}
}