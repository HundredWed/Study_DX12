#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "Material.h"

void Mesh::Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexbuffer)
{
	CreateVertexBuffer(vertexBuffer);
	CreateIndexBuffer(indexbuffer);
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//삼각형 작업
	//VertexBuffer
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)
	//IndexBuffer
	CMD_LIST->IASetIndexBuffer(&_indexBufferView);

	//dx12의 랜더링 파이프 라인의 rootargyment
	//CommitTable의 SetGraphicsRootDescriptorTable로 레지스트에 올려주는 작업
	//SetGraphicsRootDescriptorTable는 SetDescriptorHeaps과 같이 써야한다(CommandQueue 클래스)
	GEngine->GetTableDescHeap()->CommitTable();

	//CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0); VertexBuffer only 버전
	CMD_LIST->DrawIndexedInstanced(_indexCount, 1, 0, 0, 0);
}

void Mesh::CreateVertexBuffer(const vector<Vertex>& buffer)
{
	_vertexCount = static_cast<uint32>(buffer.size());
	uint32 bufferSize = _vertexCount * sizeof(Vertex);

	//정점에대한 정보를 저장할 공간 할당(line: ~57)
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
	::memcpy(vertexDataBuffer, &buffer[0], bufferSize);
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

void Mesh::CreateIndexBuffer(const vector<uint32>& buffer)
{
	_indexCount = static_cast<uint32>(buffer.size());
	uint32 bufferSize = _indexCount * sizeof(uint32);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_indexBuffer));

	void* indexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_indexBuffer->Map(0, &readRange, &indexDataBuffer);
	::memcpy(indexDataBuffer, &buffer[0], bufferSize);
	_indexBuffer->Unmap(0, nullptr);

	_indexBufferView.BufferLocation = _indexBuffer->GetGPUVirtualAddress();
	_indexBufferView.Format = DXGI_FORMAT_R32_UINT;//uint32 타입으로 받아 주기 때문에 R32로 설정. 
	_indexBufferView.SizeInBytes = bufferSize;
}
