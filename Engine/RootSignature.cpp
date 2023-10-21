#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//����
	//https://learn.microsoft.com/en-us/windows/win32/direct3d12/example-root-signatures
	//'Adding a root Constant Buffer View' �׸�
	// �� ����� ������ �ִ�. 
	// rootarguments���� ũ�⿡ ������ �ֱ� ������ ���� �ø� ���� ����.
	// ������ �����ؼ� table������ ���� ���� ����ȴ�.
	//CD3DX12_ROOT_PARAMETER param[2];
	//param[0].InitAsConstantBufferView(0); // 0�� -> b0 -> CBV 
	//param[1].InitAsConstantBufferView(1); // 1�� -> b1 -> CBV

	//���̺��� ���빰 ����
	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 0), // b0~b4
	};
	CD3DX12_ROOT_PARAMETER param[1];//���̺� �ϳ�
	param[0].InitAsDescriptorTable(_countof(ranges), ranges);

	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param);//D3D12_DEFAULT/*�⺻����*/
	/*CD3DX12_ROOT_SIGNATURE_DESC(CD3DX12_DEFAULT)
	{
		Init(0, NULL, 0, NULL, D3D12_ROOT_SIGNATURE_FLAG_NONE);
	}*/

	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // �Է� ������ �ܰ�

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&_signature));
}
