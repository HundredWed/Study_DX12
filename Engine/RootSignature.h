#pragma once

// GPU���� �۾��� �ñ� �� 
// �۾��� ������� �ϰڴٴ� ���� �˸��� Ŭ����?

//ĳ���۾��� ����������
//descriptor���� �о� �� �� �߰� �ܰ谡 �ִ�
//�� �ܰ�� �� �ٷ� �� �ܰ谡 �������� �����ε�
//�ش� �������� ������ ��� �� ������ ������ �س��� ���̶�� ������ �����ϸ� �ǰڴ� 
class RootSignature
{
public:
	void Init();

	ComPtr<ID3D12RootSignature>	GetSignature() { return _signature; }

private:
	void CreateSamplerDesc();
	void CreateRootSignature();

private:
	ComPtr<ID3D12RootSignature>	_signature;
	D3D12_STATIC_SAMPLER_DESC _samplerDesc;
};

