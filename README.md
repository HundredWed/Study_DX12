# Study_DX12
DX12 공부

## 1회차
일단 크게 숲을 보자

### 현 시점까지의 이해

- 모든 명령은 CPU에서 시작하고 CPU가 버퍼를 들고 GPU에 공간을 예약하며, GPU는 받을 때 CPU가 만든 버퍼 정보를 복사하여 예약한 공간에 실제 데이터를만드는 식이다.

- 왜 이런 과정을 거처야 하나? 지금 운영체제를 조금 듣고 이해한 바로는 CPU는 계산이 어어어엄청 빠르며 GPU는 그에 비해 계산이 느리다. CPU는 외에 할일도 많고 CPU가 주는 족족 느린 GPU가 일을하면 부담되기 때문에 
SwapChain & DescriptorHeap로 공간을 예약(및 분담)하고 RootSignature에서 테이블을 만들어 관리하며, 레지스터에 올릴 때 해당 주소를 올려 작업을 하는 식.

- 모든 작업의 순서들은 쉽게 말해 일의 효율을 위해 만들어졌다고 이해하자. 

Device -> SwapChain & DescriptorHeap -> RootSignature(캐싱) -> CommandQueue -> Render

CommandQueue: 작업할 내용들을 모아두었다가 한꺼번에 실행

SwapChain & DescriptorHeap: 버퍼를 만들어 swapChain에 넣어줌 

Device: 작업할 그래픽카드를 설정

RootSignature: 버퍼를 받아 레지스트리에 올릴 때 포인터처럼 영역을 지정

