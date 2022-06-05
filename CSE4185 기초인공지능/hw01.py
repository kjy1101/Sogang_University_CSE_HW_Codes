###### Write Your Library Here ###########
from collections import deque




#########################################


def search(maze, func):
    return {
        "bfs": bfs,
        "astar": astar,
        "astar_four_circles": astar_four_circles,
        "astar_many_circles": astar_many_circles
    }.get(func)(maze)


# -------------------- Stage 01: One circle - BFS Algorithm ------------------------ #

def bfs(maze):
    """
    [문제 01] 제시된 stage1의 맵 세가지를 BFS Algorithm을 통해 최단 경로를 return하시오.(20점)
    """
    start_point=maze.startPoint()

    path=[]

    ####################### Write Your Code Here ################################

    # 미로 => 그래프 변환
    graph = []
    gridDim = maze.getDimensions()
    for row in range(gridDim[0]):
        for col in range(gridDim[1]):
            graph.append([])
            for neighbor in maze.neighborPoints(row, col):
                graph[gridDim[1]*row+col].append(gridDim[1]*neighbor[0]+neighbor[1])


    visited = [False] * (gridDim[0]*gridDim[1])
    queue = deque([start_point[0]*gridDim[1]+start_point[1]]) #시작점
    visited[start_point[0]*gridDim[1]+start_point[1]] = True
    parent = [0] * (gridDim[0]*gridDim[1])

    while queue:
        v = queue.popleft()
        x = v // gridDim[1]
        y = v % gridDim[1]
        #path += [(x,y)]
        if maze.isObjective(x,y):
            endpoint = gridDim[1]*x + y
        #    break
        for i in graph[v]:
            if not visited[i]:
                queue.append(i)
                visited[i] = True
                parent[i] = v

    #print(parent)
    #print(x)
    #print(y)
    #endpoint = gridDim[1]*x + y
    while parent[endpoint] != endpoint:
        path += [(endpoint//gridDim[1], endpoint%gridDim[1])]
        endpoint = parent[endpoint]

    path.reverse()
    #print(path)
    #print(maze.isValidPath(path))

    """print(maze.isObjective(5,5)) #목적지인지 아닌지
    print(maze.circlePoints()) #목적지 좌표
    print(maze.neighborPoints(3,4)) #이웃한 점의 좌표
    print(maze.isValidPath(path)) #경로 타당성? 검사"""

    return path

    ############################################################################



class Node:
    def __init__(self,parent,location):
        self.parent=parent
        self.location=location #현재 노드

        self.obj=[]

        # F = G+H
        self.f=0 # 출발지점에서 목적지까지의 총 cost 합
        self.g=0 # 현재 노드에서 출발 지점까지의 총 cost
        self.h=0 # 휴리스틱, 현재 노드에서 목적지까지의 추정 거리

    def __eq__(self, other):
        return self.location==other.location and str(self.obj)==str(other.obj)

    def __le__(self, other):
        return self.g+self.h<=other.g+other.h

    def __lt__(self, other):
        return self.g+self.h<other.g+other.h

    def __gt__(self, other):
        return self.g+self.h>other.g+other.h

    def __ge__(self, other):
        return self.g+self.h>=other.g+other.h


# -------------------- Stage 01: One circle - A* Algorithm ------------------------ #

def manhatten_dist(p1,p2):
    return abs(p1[0]-p2[0])+abs(p1[1]-p2[1])

def astar(maze):

    """
    [문제 02] 제시된 stage1의 맵 세가지를 A* Algorithm을 통해 최단경로를 return하시오.(20점)
    (Heuristic Function은 위에서 정의한 manhatten_dist function을 사용할 것.)
    """

    start_point=maze.startPoint()

    end_point=maze.circlePoints()[0]

    path=[]

    ####################### Write Your Code Here ################################

    startNode = Node(None, start_point)
    endNode = Node(None, end_point)
    openList = []   #중간 계산 결과 저장
    closedList = [] #최종 결과 저장

    openList.append(startNode)

    while openList:

        currentNode = openList[0]
        currentIdx = 0

        index = 0
        for item in openList:
            if currentNode.f > item.f:
                currentNode = item
                currentIdx = index
            index += 1

        openList.pop(currentIdx) # openList에서 빼고
        closedList.append(currentNode) # closedList에 추가

        if currentNode == endNode: #현재 노드가 목적지면
            current = currentNode
            while current is not None:
                path.append(current.location)
                current = current.parent #부모를 거슬러 올라가서 경로 추가
            break

        # 현재 노드와 인접한 노드들 추가하고 f,g,h 계산해서 업데이트
        children = []
        for neighbor in maze.neighborPoints(currentNode.location[0], currentNode.location[1]):
            newchild = Node(currentNode, neighbor)
            children.append(newchild)

        for child in children:
            if child in closedList:
                continue

            child.g = currentNode.g + 1
            child.h = manhatten_dist(child.location, endNode.location)
            child.f = child.g + child.h

            flag = 0
            for openListNode in openList:
                if (child == openListNode) and (child.g > openListNode.g):
                    flag = 1
                    break
            
            if flag == 1:
                continue

            openList.append(child)

    path.reverse()
    #print(maze.isValidPath(path))
    return path

    ############################################################################


# -------------------- Stage 02: Four circles - A* Algorithm  ------------------------ #



def stage2_heuristic(p1, e1,e2,e3,e4):
    distance = []
    distance.append(((p1[0]-e1[0])**2+(p1[1]-e1[1])**2)**(1/2))
    distance.append(((p1[0]-e2[0])**2+(p1[1]-e2[1])**2)**(1/2))
    distance.append(((p1[0]-e3[0])**2+(p1[1]-e3[1])**2)**(1/2))
    distance.append(((p1[0]-e4[0])**2+(p1[1]-e4[1])**2)**(1/2))
    return min(distance)


def astar_four_circles(maze):
    """
    [문제 03] 제시된 stage2의 맵 세가지를 A* Algorithm을 통해 최단 경로를 return하시오.(30점)
    (단 Heurstic Function은 위의 stage2_heuristic function을 직접 정의하여 사용해야 한다.)
    """

    end_points=maze.circlePoints()
    end_points.sort()

    path=[]

    ####################### Write Your Code Here ################################

    start_point=maze.startPoint()
    startNode = Node(None, start_point)
    endNode1 = Node(None, end_points[0])
    endNode2 = Node(None, end_points[1])
    endNode3 = Node(None, end_points[2])
    endNode4 = Node(None, end_points[3])
    endNodeList = []
    endNodeList.append(endNode1)
    endNodeList.append(endNode2)
    endNodeList.append(endNode3)
    endNodeList.append(endNode4)

    openList = []   #중간 계산 결과 저장
    closedList = [] #최종 결과 저장

    openList.append(startNode)

    while openList:

        currentNode = openList[0]
        currentIdx = 0

        index = 0
        for item in openList:
            if item.h == 0:
                currentNode = item
                currentIdx = index
                break
            if currentNode.f > item.f:
                currentNode = item
                currentIdx = index
            index += 1

        openList.pop(currentIdx) # openList에서 빼고
        closedList.append(currentNode) # closedList에 추가

        if currentNode in endNodeList: #현재 노드가 목적지면
            current = currentNode
            endNodeList.remove(currentNode)
            startNode = current
            openList.clear()
            closedList.clear()
            openList.append(startNode)
            if len(endNodeList) == 0:
                while current is not None:
                    path.append(current.location)
                    current = current.parent #부모를 거슬러 올라가서 경로 추가
                break
            else:
                continue

        # 현재 노드와 인접한 노드들 추가하고 f,g,h 계산해서 업데이트
        children = []
        for neighbor in maze.neighborPoints(currentNode.location[0], currentNode.location[1]):
            newchild = Node(currentNode, neighbor)
            children.append(newchild)
        
        for child in children:
            if child in closedList:
                continue

            child.g = currentNode.g + 1
            child.h = stage2_heuristic(child.location, endNode1.location, endNode2.location, endNode3.location, endNode4.location)
            child.f = child.g + child.h

            flag = 0
            for openListNode in openList:
                if (child == openListNode) and (child.g > openListNode.g):
                    flag = 1
                    break
            
            if flag == 1:
                continue

            openList.append(child)

    path.reverse()
    #print(path)
    #print(maze.isValidPath(path))
    return path

    ############################################################################



# -------------------- Stage 03: Many circles - A* Algorithm -------------------- #
parent = {}
rank = {}

def find(v):
    #print("find", v)
    if parent[v] == v:
        return v
    parent[v] = find(parent[v])
    return parent[v]

def union(v, u):
    Px = find(v)
    Py = find(u)
    if Px == Py:
        return 0
    else:
        if rank[Px] > rank[Py]:
            parent[Py] = Px
        elif rank[Px] < rank[Py]:
            parent[Px] = Py
        elif rank[Px] == rank[Py]:
            parent[Py] = Px
            rank[Px] += 1
        return 1

def mst(maze, left_point, p1, endNodeList):

    cost_sum=0
    ####################### Write Your Code Here ################################
    #print("mst")
    #for point in left_point:
    #    print(point.location)
    gridDim = maze.getDimensions()
    distance = []
    for endNode in endNodeList:
        distance.append(((p1.location[0]-endNode.location[0])**2+(p1.location[1]-endNode.location[1])**2)**(1/2))
    min_distance = min(distance)
    #gridDim[1]*v.location[0]+v.location[1]
    edges = []
    for v in left_point:
        parent[gridDim[1]*v.location[0]+v.location[1]] = gridDim[1]*v.location[0]+v.location[1]
        rank[gridDim[1]*v.location[0]+v.location[1]] = 0
    #print(parent)
    for v in left_point:
        for neighbor in maze.neighborPoints(v.location[0], v.location[1]):
            newchild = Node(None, neighbor)
            if newchild in left_point:
                edges.append((min_distance, gridDim[1]*v.location[0]+v.location[1], gridDim[1]*neighbor[0]+neighbor[1]))

    mst = []
    edges.sort()
    #print(edges)
    
    for edge in edges:
        weight, v, u = edge
        #print("v:", v)
        #print("u:", u)
        #print("parent:", parent)
        if find(v) != find(u):
            union(v, u)
            mst.append(edge)

    #print(mst)
    for node in mst:
        weight, v, u = node
        cost_sum += weight

    return cost_sum

    ############################################################################


def stage3_heuristic(p1, closedList, maze, every_point, endNodeList):
    #left_point = [x for x in every_point if x not in closedList]
    #cost_sum = mst(maze, left_point, p1, endNodeList) #아직 방문하지 않은 노드들로 MST 만들어서 cost sum 계산
    if p1 in endNodeList:
        return 0
    else:
        left_point = [x for x in every_point if x not in closedList]
        cost_sum = mst(maze, left_point, p1, endNodeList)
    return cost_sum


def astar_many_circles(maze):
    """
    [문제 04] 제시된 stage3의 맵 세가지를 A* Algorithm을 통해 최단 경로를 return하시오.(30점)
    (단 Heurstic Function은 위의 stage3_heuristic function을 직접 정의하여 사용해야 하고, minimum spanning tree
    알고리즘을 활용한 heuristic function이어야 한다.)
    """

    end_points= maze.circlePoints()
    end_points.sort()

    path=[]

    ####################### Write Your Code Here ################################
    
    gridDim = maze.getDimensions()
    every_point = []
    for row in range(gridDim[0]):
        for col in range(gridDim[1]):
            if maze.isWall(row, col) == 0:
                newNode = Node(None, (row, col))
                every_point.append(newNode)

    #print(every_point)

    start_point=maze.startPoint()
    startNode = Node(None, start_point)
    endNodeList = []
    for end_point in end_points:
        endNode = Node(None, end_point)
        endNodeList.append(endNode)

    openList = []   #중간 계산 결과 저장
    closedList = [] #최종 결과 저장

    openList.append(startNode)

    while openList:

        currentNode = openList[0]
        currentIdx = 0

        index = 0
        for item in openList:
            if item.h == 0:
                currentNode = item
                currentIdx = index
                break
            if currentNode.f > item.f:
                currentNode = item
                currentIdx = index
            index += 1

        openList.pop(currentIdx) # openList에서 빼고
        closedList.append(currentNode) # closedList에 추가
        heuristic = stage3_heuristic(currentNode, closedList, maze, every_point, endNodeList)

        if currentNode in endNodeList: #현재 노드가 목적지면
            current = currentNode
            endNodeList.remove(currentNode)
            startNode = current
            openList.clear()
            closedList.clear()
            openList.append(startNode)
            if len(endNodeList) == 0:
                while current is not None:
                    path.append(current.location)
                    current = current.parent #부모를 거슬러 올라가서 경로 추가
                break
            else:
                continue

        # 현재 노드와 인접한 노드들 추가하고 f,g,h 계산해서 업데이트
        children = []
        for neighbor in maze.neighborPoints(currentNode.location[0], currentNode.location[1]):
            newchild = Node(currentNode, neighbor)
            children.append(newchild)
        
        for child in children:
            if child in closedList:
                continue

            child.g = currentNode.g + 1
            child.h = heuristic#stage3_heuristic(child, closedList, maze, every_point, endNodeList)
            child.f = child.g + child.h

            flag = 0
            for openListNode in openList:
                if (child == openListNode) and (child.g > openListNode.g):
                    flag = 1
                    break
            
            if flag == 1:
                continue

            openList.append(child)

    path.reverse()
    #print(path)
    #print(maze.isValidPath(path))

    return path

    ############################################################################
