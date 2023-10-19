#pragma once

//사실 CommandQueue나 DescriptorHaep등 엔진에 있는 기능을
//여기 다 때려넣는 게 보통이다
//하지만 그러면 구조를 파악하기 어렵기 때문에 분리했다.

class Engine
{
public:

	void Init(const WindowInfo& info);
	void Render();

public:
	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height);

private:
	// 그려질 화면 크기 관련
	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	/**핵심*/
	shared_ptr<class Device>			 _device;
	shared_ptr<class CommandQueue>		 _cmdQueue;
	shared_ptr<class SwapChain>			 _swapChain;
	shared_ptr<class DescriptorHeap>	 _descHeap;
};

