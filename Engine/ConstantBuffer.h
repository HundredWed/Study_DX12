#pragma once

// 1ȸ�� ����
// cmdQ�� ���߿� �ѹ��� �۾��ϵ����Ѵ�.
// ������ ���۸� �ϳ��� ����µ�
// �̷��� �ϸ� ���� �ﰢ���� �ι� ��û�� ���� ��
// �ι�° �ﰢ���� ù��° �ﰢ���� ���� ���� ������ �߻��� �� �ִ�
// ���� �ι�° ��û�� ���� �ٸ� ���۸� ����� �۾��� �� ����Ѵ�


class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(uint32 size, uint32 count);

	void Clear();
	//void PushData(int32 rootParamIndex, void* buffer, uint32 size);
	D3D12_CPU_DESCRIPTOR_HANDLE PushData(int32 rootParamIndex, void* buffer, uint32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(uint32 index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(uint32 index);

private:
	void CreateBuffer();
	void CreateView();

private:
	ComPtr<ID3D12Resource>		_cbvBuffer;//GPU
	BYTE*						_mappedBuffer = nullptr;//CPU
	uint32						_elementSize = 0;
	uint32						_elementCount = 0;

	ComPtr<ID3D12DescriptorHeap>		_cbvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE			_cpuHandleBegin = {};
	uint32								_handleIncrementSize = 0;

	uint32						_currentIndex = 0;
};

