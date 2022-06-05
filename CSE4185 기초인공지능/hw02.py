from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

## Example Agent
class ReflexAgent(Agent):

  def Action(self, gameState):

    move_candidate = gameState.getLegalActions()

    scores = [self.reflex_agent_evaluationFunc(gameState, action) for action in move_candidate]
    bestScore = max(scores)
    Index = [index for index in range(len(scores)) if scores[index] == bestScore]
    get_index = random.choice(Index)

    return move_candidate[get_index]

  def reflex_agent_evaluationFunc(self, currentGameState, action):

    successorGameState = currentGameState.generatePacmanSuccessor(action)
    newPos = successorGameState.getPacmanPosition()
    oldFood = currentGameState.getFood()
    newGhostStates = successorGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

    return successorGameState.getScore()



def scoreEvalFunc(currentGameState):

  return currentGameState.getScore()

class AdversialSearchAgent(Agent):

  def __init__(self, getFunc ='scoreEvalFunc', depth ='2'):
    self.index = 0
    self.evaluationFunction = util.lookup(getFunc, globals())

    self.depth = int(depth)




class MinimaxAgent(AdversialSearchAgent):
  """
    [문제 01] MiniMax의 Action을 구현하시오. (20점)
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    
    def minimax_Max_value(self, gameState, depth):
      if self.depth == depth or gameState.isWin() or gameState.isLose():
        value = self.evaluationFunction(gameState)
      else:
        value = float("-inf")
        move_candidate = gameState.getLegalPacmanActions()
        for move in move_candidate:
          successor_state = gameState.generatePacmanSuccessor(move)
          value = max(value, minimax_Min_value(self, successor_state, depth))
      return value

    def minimax_Min_value(self, gameState, depth=0, agentIndex=1):
      if self.depth == depth or gameState.isWin() or gameState.isLose():
        value = self.evaluationFunction(gameState)
      else:
        last_ghost_index = gameState.getNumAgents()-1
        if agentIndex == last_ghost_index:
          value = minimax_Min_value1(self, gameState, depth, agentIndex)
        else:
          value = minimax_Min_value2(self, gameState, depth, agentIndex)
      return value

    def minimax_Min_value1(self, gameState, depth, agentIndex): # 마지막 고스트
      value = float("inf")
      move_candidate = gameState.getLegalActions(agentIndex)
      depth += 1
      for move in move_candidate:
        successor_state = gameState.generateSuccessor(agentIndex, move)
        value = min(value, minimax_Max_value(self, successor_state, depth))
      return value

    def minimax_Min_value2(self, gameState, depth, agentIndex): # 중간 고스트
      value = float("inf")
      move_candidate = gameState.getLegalActions(agentIndex)
      agentIndex += 1
      for move in move_candidate:
        successor_state = gameState.generateSuccessor(agentIndex-1, move)
        value = min(value, minimax_Min_value(self, successor_state, depth, agentIndex))
      return value

    value_list = []
    action_list = []
    move_candidate = gameState.getLegalPacmanActions()
    
    for move in move_candidate:
      successor_state = gameState.generatePacmanSuccessor(move)
      value = minimax_Min_value(self, successor_state)
      value_list.append(value)
      action_list.append(move)

    max_value_index = value_list.index(max(value_list))
    action = action_list[max_value_index]
    
    return action

    ############################################################################






class AlphaBetaAgent(AdversialSearchAgent):
  """
    [문제 02] AlphaBeta의 Action을 구현하시오. (25점)
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################
    
    def alphabeta_Max_value(self, gameState, depth, alpha, beta):
      if self.depth == depth or gameState.isWin() or gameState.isLose():
        value = self.evaluationFunction(gameState)
      else:
        value = float("-inf")
        move_candidate = gameState.getLegalPacmanActions()
        for move in move_candidate:
          successor_state = gameState.generatePacmanSuccessor(move)
          value = max(value, alphabeta_Min_value(self, successor_state, alpha, beta, depth))
          if value >= beta:
            return value
          alpha = max(alpha, value)
      return value

    def alphabeta_Min_value(self, gameState, alpha, beta, depth=0, agentIndex=1):
      if self.depth == depth or gameState.isWin() or gameState.isLose():
        value = self.evaluationFunction(gameState)
      else:
        last_ghost_index = gameState.getNumAgents()-1
        if agentIndex == last_ghost_index:
          value = alphabeta_Min_value1(self, gameState, alpha, beta, depth, agentIndex)
        else:
          value = alphabeta_Min_value2(self, gameState, alpha, beta, depth, agentIndex)
      return value

    def alphabeta_Min_value1(self, gameState, alpha, beta, depth, agentIndex): # 마지막 고스트
      value = float("inf")
      move_candidate = gameState.getLegalActions(agentIndex)
      depth += 1
      for move in move_candidate:
        successor_state = gameState.generateSuccessor(agentIndex, move)
        value = min(value, alphabeta_Max_value(self, successor_state, depth, alpha, beta))
        if value <= alpha:
          return value
        beta = min(beta, value)
      return value

    def alphabeta_Min_value2(self, gameState, alpha, beta, depth, agentIndex): # 중간 고스트
      value = float("inf")
      move_candidate = gameState.getLegalActions(agentIndex)
      agentIndex += 1
      for move in move_candidate:
        successor_state = gameState.generateSuccessor(agentIndex-1, move)
        value = min(value, alphabeta_Min_value(self, successor_state, alpha, beta, depth, agentIndex))
        if value <= alpha:
          return value
        beta = min(beta, value)
      return value


    value_list = []
    action_list = []
    move_candidate = gameState.getLegalPacmanActions()
    alpha = float("-inf")
    beta = float("inf")
    
    for move in move_candidate:
      successor_state = gameState.generatePacmanSuccessor(move)
      value = alphabeta_Min_value(self, successor_state, alpha, beta)
      value_list.append(value)
      action_list.append(move)

    max_value_index = value_list.index(max(value_list))
    action = action_list[max_value_index]
    
    return action

    ############################################################################






class ExpectimaxAgent(AdversialSearchAgent):
  """
    [문제 03] Expectimax의 Action을 구현하시오. (25점)
    (depth와 evaluation function은 위에서 정의한 self.depth and self.evaluationFunction을 사용할 것.)
  """
  def Action(self, gameState):
    ####################### Write Your Code Here ################################

    def expecti_Max_value(self, gameState, depth):
      if self.depth == depth or gameState.isWin() or gameState.isLose():
        value = self.evaluationFunction(gameState)
      else:
        value = float("-inf")
        move_candidate = gameState.getLegalPacmanActions()
        for move in move_candidate:
          successor_state = gameState.generatePacmanSuccessor(move)
          value = max(value, expecti_Chance_value(self, successor_state, depth))
      return value

    def expecti_Chance_value(self, gameState, depth=0, agentIndex=1):
      if self.depth == depth or gameState.isWin() or gameState.isLose():
        value = self.evaluationFunction(gameState)
        return value
      else:
        value = 0
        last_ghost_index = gameState.getNumAgents()-1
        if agentIndex == last_ghost_index:
          value += expecti_Chance_value1(self, gameState, depth, agentIndex)
        else:
          value += expecti_Chance_value2(self, gameState, depth, agentIndex)
        expect_value = value / gameState.getNumAgents()
        return expect_value

    def expecti_Chance_value1(self, gameState, depth, agentIndex): # 마지막 고스트
      value = float("inf")
      move_candidate = gameState.getLegalActions(agentIndex)
      depth += 1
      for move in move_candidate:
        successor_state = gameState.generateSuccessor(agentIndex, move)
        value = expecti_Max_value(self, successor_state, depth)
      return value

    def expecti_Chance_value2(self, gameState, depth, agentIndex): # 중간 고스트
      value = float("inf")
      move_candidate = gameState.getLegalActions(agentIndex)
      agentIndex += 1
      for move in move_candidate:
        successor_state = gameState.generateSuccessor(agentIndex-1, move)
        value = expecti_Chance_value(self, successor_state, depth, agentIndex)
      return value

    value_list = []
    action_list = []
    move_candidate = gameState.getLegalPacmanActions()
    
    for move in move_candidate:
      successor_state = gameState.generatePacmanSuccessor(move)
      value = expecti_Chance_value(self, successor_state)
      value_list.append(value)
      action_list.append(move)

    max_value_index = value_list.index(max(value_list))
    action = action_list[max_value_index]

    return action

    ############################################################################
