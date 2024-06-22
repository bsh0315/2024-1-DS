/****************
 * 2023041017 백승헌
 * 
 * 그래프를 구현할 때, 방향그래프가 아닌 무방향 그래프로 구현하였습니다.
 * 
 * 또한, 정점과 엣지를 삽입할 때, BFS와 DFS의 구현의 용이성을 위해서  
 * 오름차순으로 정렬하여 구현하였습니다.
 * ****** */



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define maxVertex 10  // 최대 정점의 수를 10으로 정의

bool visited[maxVertex];  // 각 정점의 방문 여부를 나타내는 배열

// 그래프의 정점 구조체 정의
typedef struct graphNode {
    int vertex;  // 정점 번호
    struct graphNode* link;  // 다음 인접 정점을 가리키는 포인터
} graphNode;

// 그래프 구조체 정의
typedef struct graphType {
    int n;  // 그래프의 정점 개수
    graphNode* adj_list[maxVertex];  // 인접 리스트 배열
} graphType;

// 함수 선언
void Initialize_Graph(graphType* g); // 그래프 초기화 함수
void Insert_Vertex(graphType* g); // 정점 삽입 함수
void Insert_Edge(graphType* g, int num1, int num2); // 엣지 삽입 함수
void DFS(graphType* g, int v); // 깊이 우선 탐색 함수
void BFS(graphType* g, int v); // 너비 우선 탐색 함수
void Print_Graph(graphType* g); // 그래프 출력 함수
void Free_Graph(graphType* g); // 그래프 메모리 해제 함수

int main() {
    char option = 0;  // 사용자의 메뉴 선택을 저장할 변수
    graphType* g = (graphType*)malloc(sizeof(graphType));  // 그래프 동적 할당

    do {
        option = 0;

        // 메뉴 출력
        printf("\n\n[----- [백승헌] [2023041017] -----]\n");
        printf("----------------------------------------------------------------\n");
        printf("Graph Searches\n");
        printf("Initialize Graph        = z\n");
        printf("Insert Vertex           = v      Insert Edge            = e\n");
        printf("Depth First Search      = d      Breath First Search    = b\n");
        printf("Print Graph             = p      Quit                   = q\n");
        printf("----------------------------------------------------------------\n");
        printf("\n옵션 입력 => _\b");
        scanf(" %c", &option);  // 사용자 입력 받기

        switch (option) {
            case 'z':
                Initialize_Graph(g);
                break;
            case 'v':
                Insert_Vertex(g);
                break;
            case 'e': {
                int num1 = 0, num2 = 0;
                printf("연결할 두 정점을 입력하세요 => ");
                scanf("%d %d", &num1, &num2);  // 두 정점 입력 받기
                Insert_Edge(g, num1, num2);  // 엣지 삽입
                break;
            }
            case 'd':
                printf("깊이 우선 탐색\n");
                for (int i = 0; i < g->n; i++) {
                    visited[i] = false;  // 방문 배열 초기화
                }
                DFS(g, 0);  // 0번 정점부터 DFS 시작
                printf("\n");
                break;
            case 'b':
                printf("너비 우선 탐색\n");
                for (int i = 0; i < g->n; i++) {
                    visited[i] = false;  // 방문 배열 초기화
                }
                BFS(g, 0);  // 0번 정점부터 BFS 시작
                break;
            case 'p':
                Print_Graph(g);  // 그래프 출력
                break;
            case 'q':
                printf("프로그램을 종료합니다.\n");
                Free_Graph(g);  // 그래프 메모리 해제
                free(g);  // 그래프 구조체 메모리 해제
                exit(0);  // 프로그램 종료
                break;
            default:
                printf("잘못된 입력입니다.\n\b");
                break;
        }
    } while (1);  // 사용자가 'q'를 입력할 때까지 반복

    

    return 0;
}

// 그래프 초기화 함수
void Initialize_Graph(graphType* g) {
    g->n = 0;  // 정점 개수를 0으로 초기화
    for (int v = 0; v < maxVertex; ++v) {
        g->adj_list[v] = NULL;  // 모든 인접 리스트를 NULL로 초기화
    }
    printf("그래프가 초기화되었습니다.\n\n");
}

// 정점 삽입 함수
void Insert_Vertex(graphType* g) {
    if (g->n + 1 > maxVertex) {
        printf("이미 모든 정점 포화상태입니다.\n");
        return;
    }
    printf("정점 %d가 추가됨.\n\n", g->n);
    g->n += 1;  // 정점 개수 증가
}

// 엣지 삽입 함수
// 한 정점에 대해서 여러개의 edge를 가질 수 있음.
// 탐색을 할 때 작은 정점부터 탐색해야 하므로 구현의 용이성을 위해 오름차순으로 정렬하였습니다.
void Insert_Edge(graphType* g, int num1, int num2) {
    if (num1 >= g->n || num2 >= g->n) { //num1, num2가 현재 정점의 범위를 벗어날 때
        printf("현재 존재하지 않는 정점입니다.\n\n"); //오류 메시지 출력
        return;
    }

    // 정점 num1에 정점 num2를 삽입
    graphNode* new1 = (graphNode*)malloc(sizeof(graphNode)); //새로운 노드 new1 생성
    new1->vertex = num2; //new1의 vertex에 num2 저장
    new1->link = NULL; //new1의 link를 NULL로 초기화

    // 정점 num1의 인접 리스트를 오름차순으로 유지하며 삽입
    if (g->adj_list[num1] == NULL || g->adj_list[num1]->vertex > num2) { 
        //num1의 인접 리스트가 비어있거나, num1의 인접 리스트의 vertex가 num2보다 클 때
        new1->link = g->adj_list[num1]; //new1의 link에 num1의 인접 리스트를 연결
        g->adj_list[num1] = new1; //num1의 인접 리스트에 new1 연결
    } else { //num1의 인접 리스트가 비어있지 않고, num1의 인접 리스트의 vertex가 num2보다 작을 때
        graphNode* temp = g->adj_list[num1]; //temp에 num1의 인접 리스트 저장 
        while (temp->link != NULL && temp->link->vertex < num2) { 
            //temp의 link가 NULL이 아니고, temp의 link의 vertex가 num2보다 작을 때
            temp = temp->link;
            //temp에 temp의 link 저장
        }
        new1->link = temp->link; //new1의 link에 temp의 link 저장
        temp->link = new1; //temp의 link에 new1 저장
    }

    if (num1 == num2) { //num1과 num2가 같을 때는 egde의 방향을 또 추가할 필요가 없으므로 return
        printf("엣지 (%d, %d)가 추가되었습니다.\n\n", num1, num2);
        return;
    }

    // 정점 num2에 정점 num1을 삽입 (무방향 그래프이므로)
    graphNode* new2 = (graphNode*)malloc(sizeof(graphNode));
    new2->vertex = num1;
    new2->link = NULL;

    // 정점 num2의 인접 리스트를 오름차순으로 유지하며 삽입
    // 위와 동일한 방법으로 구현
    if (g->adj_list[num2] == NULL || g->adj_list[num2]->vertex > num1) {
        new2->link = g->adj_list[num2];
        g->adj_list[num2] = new2;
    } else {
        graphNode* temp = g->adj_list[num2];
        while (temp->link != NULL && temp->link->vertex < num1) {
            temp = temp->link;
        }
        new2->link = temp->link;
        temp->link = new2;
    }

    printf("엣지 (%d, %d)가 추가되었습니다.\n\n", num1, num2);
}

// 깊이 우선 탐색(DFS) 함수
void DFS(graphType* g, int v) {
    graphNode* w;
    visited[v] = true;  // 정점 v를 방문했다고 표시
    printf("정점 %d -> ", v);

    for (w = g->adj_list[v]; w; w = w->link) {  // 인접한 정점들 순회
        if (!visited[w->vertex]) {
            DFS(g, w->vertex);  // 방문하지 않은 정점에 대해 DFS 재귀 호출
        }
    }
}

// 너비 우선 탐색(BFS) 함수
void BFS(graphType* g, int v) {
    graphNode* w;
    int queue[maxVertex], front = -1, rear = -1;  // 큐 초기화
    visited[v] = true;  // 정점 v를 방문했다고 표시
    printf("정점 %d -> ", v);
    queue[++rear] = v;  // 정점 v를 큐에 삽입

    while (front < rear) {  // 큐가 비어있지 않을 때까지
        v = queue[++front];  // 큐에서 정점 하나를 꺼냄
        for (w = g->adj_list[v]; w; w = w->link) {  // 인접한 정점들 순회
            if (!visited[w->vertex]) {
                visited[w->vertex] = true;  // 정점을 방문했다고 표시
                printf("정점 %d -> ", w->vertex);
                queue[++rear] = w->vertex;  // 큐에 삽입
            }
        }
    }
}

// 그래프 출력 함수
void Print_Graph(graphType* g) {
    for (int i = 0; i < g->n; i++) { 
        graphNode* p = g->adj_list[i];
        printf("정점 %d의 인접 리스트", i);
        while (p != NULL) {
            printf("-> %d", p->vertex);
            p = p->link;
        }
        // 모든 인접 정점 출력
        printf("\n");
    }
}

// 그래프 메모리 해제 함수
void Free_Graph(graphType* g) {
    graphNode* p;
    for (int i = 0; i < g->n; i++) {
        while (g->adj_list[i] != NULL) {
            p = g->adj_list[i];
            g->adj_list[i] = p->link;
            free(p);
        }
    }
}
