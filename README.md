# Study_DX12
DX12 공부

## 1회차
일단 크게 숲을 보자

### 5일차 이해
CPU-> GPU 
Device -> SwapChain & DescriptorHeap -> RootSignature(캐싱) -> CommandQueue -> Render

CommandQueue: 작업할 내용들을 모아두었다가 한꺼번에 실행

SwapChain & DescriptorHeap: 버퍼를 만들어 swapChain에 넣어줌 

Device: 작업할 그래픽카드를 설정

RootSignature: 버퍼를 받아 레지스트리에 올릴 때 포인터처럼 영역을 지정

