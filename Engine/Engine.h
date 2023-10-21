#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"

//��� CommandQueue�� DescriptorHaep�� ������ �ִ� �����
//���� �� �����ִ� �� �����̴�
//������ �׷��� ������ �ľ��ϱ� ��Ʊ� ������ �и��ߴ�.

class Engine
{
public:

	void Init(const WindowInfo& info);
	void Render();

public:

	//Engine�� �������� �����߱� ������(GEngine) �ش� �Լ����� �ش� ���� ������ �ʿ��� �� 
	//GEngine���� �ٷ� �޾ƿ��� ���ؼ� �������
	//�ٸ�, �̰��� �������� ���ڷ� �޾ƿ� ������ ������, �������� �ٷ� �����ð������� ���� ���������̱� ������
	//���� ���� �ʿ�� ����. 
	//������ ���Ǹ� ���󰡸鼭 ���� ���̱� ������ �Ȱ��� ����.
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
	// �׷��� ȭ�� ũ�� ����
	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	/**�ٽ�*/
	shared_ptr<Device>				 _device;
	shared_ptr<CommandQueue>		 _cmdQueue;
	shared_ptr<SwapChain>			 _swapChain;
	shared_ptr<RootSignature>		 _rootSignature;
	shared_ptr<ConstantBuffer>		_cb;
	shared_ptr<TableDescriptorHeap> _tableDescHeap;
};

