#pragma once


// [기안서]
// 외주를 맡길 때 이런 저런 정보들을 같이 넘겨줘야 하는데,
// 아무 형태로나 요청하면 못 알아먹는다
// - 각종 리소스를 어떤 용도로 사용하는지 꼼꼼하게 적어서 넘겨주는 용도

// 요약하자면 swapchain에서 리소스를 만들어 주고
// 그것을 그대로 넘기는 것이 아니라 그 리소스로 어떻게 작업해달라는 설계도를 넘기는 것 
// 즉, 우리가 코드를 치면 컴파일해서 컴퓨터가 알아먹더록 하듯이
// 리소스를 만들어 GPU가 알아 먹도록 해주는 것.

class DescriptorHeap // dx11의 View
{
public:
	void Init(ComPtr<ID3D12Device> device, shared_ptr<class SwapChain> swapChain);

	D3D12_CPU_DESCRIPTOR_HANDLE		GetRTV(int32 idx) { return _rtvHandle[idx]; }

	D3D12_CPU_DESCRIPTOR_HANDLE		GetBackBufferView();

private:
	ComPtr<ID3D12DescriptorHeap>	_rtvHeap;
	uint32							_rtvHeapSize = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE		_rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

	shared_ptr<class SwapChain>		_swapChain;
};
