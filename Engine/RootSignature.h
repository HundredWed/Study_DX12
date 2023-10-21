#pragma once

// GPU에게 작업을 맡길 때 
// 작업을 어떤식으로 하겠다는 것을 알리는 클래스?

//캐싱작업과 마찬가지로
//descriptor에서 읽어 올 때 중간 단계가 있다
//그 단계들 중 바로 밑 단계가 레지스터 영역인데
//해당 레지스터 영역을 어떻게 쓸 것인지 사인을 해놓는 것이라고 지금은 이해하면 되겠다 
class RootSignature
{
public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature>	GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature>	_signature;
};

