#pragma once

// 1회자 이해
// cmdQ는 나중에 한번에 작업하도록한다.
// 지금은 버퍼를 하나만 만드는데
// 이렇게 하면 만약 삼각형을 두번 요청을 했을 때
// 두번째 삼각형이 첫번째 삼각형을 덮어 쓰는 문제가 발생할 수 있다
// 따라서 두번째 요청이 오면 다른 버퍼를 만드는 작업을 해 줘야한다


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

