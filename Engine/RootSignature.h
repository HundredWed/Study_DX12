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
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature>	GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature>	_signature;
};

