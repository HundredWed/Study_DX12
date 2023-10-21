#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//서명
	//https://learn.microsoft.com/en-us/windows/win32/direct3d12/example-root-signatures
	//'Adding a root Constant Buffer View' 항목
	// 이 방법엔 단점이 있다. 
	// rootarguments에는 크기에 제한이 있기 때문에 마냥 늘릴 수는 없다.
	// 때문에 웬만해선 table형식을 쓰는 것이 권장된다.
	//CD3DX12_ROOT_PARAMETER param[2];
	//param[0].InitAsConstantBufferView(0); // 0번 -> b0 -> CBV 
	//param[1].InitAsConstantBufferView(1); // 1번 -> b1 -> CBV

	//테이블의 내용물 설정
	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 0), // b0~b4
	};
	CD3DX12_ROOT_PARAMETER param[1];//테이블 하나
	param[0].InitAsDescriptorTable(_countof(ranges), ranges);

	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param);//D3D12_DEFAULT/*기본상태*/
	/*CD3DX12_ROOT_SIGNATURE_DESC(CD3DX12_DEFAULT)
	{
		Init(0, NULL, 0, NULL, D3D12_ROOT_SIGNATURE_FLAG_NONE);
	}*/

	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 입력 조립기 단계

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&_signature));
}
