#pragma once

// GPU에게 작업을 맡길 때 
// 작업을 어떤식으로 하겠다는 것을 알리는 클래스?


class RootSignature
{
public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature>	GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature>	_signature;
};

