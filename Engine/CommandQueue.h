#pragma once
//dx9 �������� ����̽��� ���ؼ� �� �� �� �� �۾��� ���� ����
//dx12�� �Ѿ���鼭 �����ϰ� �ٲ�
//25:59~

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);
	
	//fence�� ���� �۾��� ��ٸ� ��
	void WaitSync();

	/**�ٽ� line: ~22*/
	//���������� ������ �׸��� �κ�
	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	void FlushResourceCommandQueue();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return _cmdList; }
	ComPtr<ID3D12GraphicsCommandList> GetResourceCmdList() { return	_resCmdList; }

private:

	/**�ٽ� Line: ~47*/
	// CommandQueue : DX12�� ����
	// ���ָ� ��û�� ��, �ϳ��� ��û�ϸ� ��ȿ����
	// [���� ���]�� �ϰ��� �������� ����ߴٰ� �� �濡 ��û�ϴ� ��
	ComPtr<ID3D12CommandQueue>			_cmdQueue;	//�ϰ��� ������ ť
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;	//�ϰ� �ϰ���ü�� �޸� ����
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;	//�ϰ� ����Ʈ

	// �ؽ����� CreateTexture�Լ����� CMDLIST�� ���� �۾��� �ϰ� �Ǵµ�
	// ����Ʈ�� CommandQueue�� RenderBegine ���� �ʱ�ȭ�Ͽ� ���۵ǰ�
	// RenderEnd �� Close�� �� �ش�.
	// �׷� �ؽ�ó�� RenderBegine�� RenderEnd�� ���̿����� ���� �� �ִٴ� ���ε�
	// ���� �׷������� ���� �� ���̿� �۾��� �ϴ� ��쵵 �ſ� ����(�� �Ѵ�. � �������� �׷��� ���� ���ذ� ���� �ʴ´�.)
	// �׷��� ���� ���ҽ� �ε� �뵵�� ����� �������� ����� ���.
	ComPtr<ID3D12CommandAllocator>		_resCmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	_resCmdList;

	// Fence : ��Ÿ��(?)
	// CPU / GPU ����ȭ�� ���� ������ ����
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>		_swapChain;
};

