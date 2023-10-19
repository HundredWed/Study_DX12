#pragma once
//dx9 시절에는 디바이스를 통해서 그 때 그 때 작업을 던져 줬음
//dx12로 넘어오면서 복잡하게 바뀜


class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain, shared_ptr<DescriptorHeap> descHeap);
	
	//fence로 인해 작업을 기다릴 때
	void WaitSync();

	/**핵심 line: ~22*/
	//실질적으로 게임을 그리는 부분
	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }

private:

	/**핵심 lin:~30*/
	// CommandQueue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것
	ComPtr<ID3D12CommandQueue>			_cmdQueue;	//일감을 저장할 큐
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;	//일감 일감자체의 메모리 관리
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;	//일감 리스트

	// Fence : 울타리(?)
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>		_swapChain;
	shared_ptr<DescriptorHeap>	_descHeap;
};

