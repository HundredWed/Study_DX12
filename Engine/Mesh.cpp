#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(vector<Vertex>& vec)
{
	_vertexCount = static_cast<uint32>(vec.size());
	uint32 bufferSize = _vertexCount * sizeof(Vertex);

	//정점에대한 정보를 저장할 공간 할당(line: ~20)
	//D3D12_HEAP_TYPE_UPLOAD타입들에 대해선 후에 알아보자
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	//리소스(_vertexBuffer) 제작
	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer));

	// Copy the triangle data to the vertex buffer.
	void* vertexDataBuffer = nullptr;//주문서?
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.

	//GPU에 주문서 투척
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &vec[0], bufferSize);
	_vertexBuffer->Unmap(0, nullptr);

	//여기까지 요약하자면 
	//CPU에서 정점에 대한 정보를 받아 그 공간을 만들고
	//공간에다가 바로 만드는 것이 아니라 복사하여 저장한 후 
	//GPU는 그 복사값을 보고 메쉬를 만들게 된다?
	//즉, CPU에서 주문을 하면 공간을 예약하고 주문서를 만들어 GPU에 주고 GPU는 주문서대로 만든다?
	//CPU와 GPU의 동작방식에 대해 알아봐야할 것 같다.

	// Initialize the vertex buffer view.
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex); // 정점 1개 크기
	_vertexBufferView.SizeInBytes = bufferSize; // 버퍼의 크기
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)

	//TODO
	// 1) Buffer에다가 데이터 세팅
	// 2) Buffer의 주소를 register에다가 전송
	GEngine->GetCB()->PushData(0, &_transform, sizeof(_transform));
	GEngine->GetCB()->PushData(1, &_transform, sizeof(_transform));

	CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0);
}
