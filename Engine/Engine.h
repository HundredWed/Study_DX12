#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"

//사실 CommandQueue나 DescriptorHaep등 엔진에 있는 기능을
//여기 다 때려넣는 게 보통이다
//하지만 그러면 구조를 파악하기 어렵기 때문에 분리했다.

class Engine
{
public:

	void Init(const WindowInfo& info);
	void Render();

public:

	//Engine을 전역으로 설정했기 때문에(GEngine) 해당 함수들은 해당 리턴 값들이 필요할 때 
	//GEngine에서 바로 받아오기 위해서 만들었다
	//다만, 이것은 어디까지나 인자로 받아와 저장할 것인지, 전역에서 바로 가져올걸인지에 대한 취향차이이기 때문에
	//굳이 해줄 필요는 없다. 
	//지금은 강의를 따라가면서 배우는 중이기 때문에 똑같이 해줌.
	shared_ptr<Device> GetEngineDivce() { return _device; }
	shared_ptr<CommandQueue> GetCmdQueue() { return _cmdQueue; }
	shared_ptr<SwapChain> GetSwapChaine() { return _swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	shared_ptr<ConstantBuffer> GetCB() { return _cb; }
	shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return _tableDescHeap; }

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
	shared_ptr<Device>				 _device;
	shared_ptr<CommandQueue>		 _cmdQueue;
	shared_ptr<SwapChain>			 _swapChain;
	shared_ptr<RootSignature>		 _rootSignature;
	shared_ptr<ConstantBuffer>		_cb;
	shared_ptr<TableDescriptorHeap> _tableDescHeap;
};

