#pragma once
//dx9 시절에는 디바이스를 통해서 그 때 그 때 작업을 던져 줬음
//dx12로 넘어오면서 복잡하게 바뀜
//25:59~

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);
	
	//fence로 인해 작업을 기다릴 때
	void WaitSync();

	/**핵심 line: ~22*/
	//실질적으로 게임을 그리는 부분
	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	void FlushResourceCommandQueue();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return _cmdList; }
	ComPtr<ID3D12GraphicsCommandList> GetResourceCmdList() { return	_resCmdList; }

private:

	/**핵심 Line: ~47*/
	// CommandQueue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것
	ComPtr<ID3D12CommandQueue>			_cmdQueue;	//일감을 저장할 큐
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;	//일감 일감자체의 메모리 관리
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;	//일감 리스트

	// 텍스쳐의 CreateTexture함수에서 CMDLIST를 통해 작업을 하게 되는데
	// 리스트는 CommandQueue의 RenderBegine 에서 초기화하여 시작되고
	// RenderEnd 때 Close를 해 준다.
	// 그럼 텍스처를 RenderBegine와 RenderEnd의 사이에서만 만들 수 있다는 것인데
	// 굳이 그럴이유가 없고 그 사이에 작업을 하는 경우도 매우 낮다(고 한다. 어떤 이유에서 그런진 아직 이해가 되지 않는다.)
	// 그래서 따로 리소스 로드 용도를 사용할 변수들을 만들어 줬다.
	ComPtr<ID3D12CommandAllocator>		_resCmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_resCmdList;

	// Fence : 울타리(?)
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>		_swapChain;
};

