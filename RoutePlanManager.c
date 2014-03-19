/*
 * this C source file supply route plan algorithm
 * 
 * Description:
 * 1->support instantiate mode and singleton mode
 * 2->calculate route point from start to end
 * 3->supply core route plan algorithm with relate data
 * 
 * Usage:
 * 1->Instantiation:
 * RoutePlanManager rpMgr = new RoutePlanManager();
 * 2->singleton:
 * RoutePlanManager rpMgr = RoutePlanManager->getInstance();
 * 
 * rpMgr->initTestStationList();
 * 
 * ArrayList<RouteData> result = rpMgr->getRoutes(0, 1);
 * 
 * Author:
 * 
 * Zhang Xuyang
 * 
 * 2014-03-13
 */

#include "RoutePlanManager.h"

StationListNode* mStationNodeListHead = NULL;

//example data codes
void initTestStationList()
{
	//A
	addStationNode0(0);

	//AB
	addToStationPara0(0, 1, 5);

	//AD
	addToStationPara0(0, 3, 5);

	//AE
	addToStationPara0(0, 4, 7);

	//B
	addStationNode0(1);

	//BC
	addToStationPara0(1, 2, 4);

	//C
	addStationNode0(2);

	//CD
	addToStationPara0(2, 3, 8);

	//CE
	addToStationPara0(2, 4, 2);

	//D
	addStationNode0(3);

	//DC
	addToStationPara0(3, 2, 8);

	//DE
	addToStationPara0(3, 4, 6);

	//E
	addStationNode0(4);

	//EB
	addToStationPara0(4, 1, 3);
}

int addStationNode0(int stationID)
{
	return addStationNode3(
			mStationNodeListHead,
			stationID,
			NULL);
}

int addStationNode1(
		int stationID,
		void* extraData)
{
	return addStationNode3(
			mStationNodeListHead,
			stationID,
			extraData);
}

int addStationNode2(
		StationListNode* stationNodeListPtr,
		int stationID)
{
	return addStationNode3(
			stationNodeListPtr,
			stationID,
			NULL);
}

int addStationNode3(
		StationListNode* stationNodeListPtr,
		int stationID,
		void* extraData)
{
	StationNode* stationNode = getStationNode(stationNodeListPtr, stationID);

	if(stationNode == NULL)
	{
		stationNode = (StationNode*)malloc(sizeof(StationNode));
		
		stationNode->thisStationID = stationID;
		
		stationNode->extraData = extraData;

		if(stationNodeListPtr == NULL)
		{
			if(mStationNodeListHead == NULL)
			{
				mStationNodeListHead = (StationListNode*)malloc(sizeof(StationListNode));

				mStationNodeListHead->stationNode = stationNode;

				mStationNodeListHead->pre = NULL;

				mStationNodeListHead->next = NULL;
			}
			else
			{
				StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

				stationListNode->stationNode = stationNode;

				stationListNode->next = NULL;

				StationListNode* tmpPtr = mStationNodeListHead;

				for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
				{
					if(tmpPtr->next == NULL)
					{
						stationListNode->pre = tmpPtr;

						tmpPtr->next = stationListNode;

						tmpPtr = tmpPtr->next;

						break;
					}
				}
			}

			stationNodeListPtr = mStationNodeListHead;
		}
		else
		{
			StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

			stationListNode->stationNode = stationNode;

			stationListNode->next = NULL;

			StationListNode* tmpPtr = stationNodeListPtr;

			for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{
				if(tmpPtr->next == NULL)
				{
					stationListNode->pre = tmpPtr;

					tmpPtr->next = stationListNode;

					tmpPtr = tmpPtr->next;

					break;
				}
			}
		}
	}
	else
	{
		return ERouteMgrError.EStationNodeExisted;
	}

	return ERouteMgrError.ESuccess;
}

StationNode* getStationNode(
		StationListNode* stationNodeListPtr,
		int thisStationID)
{
	if(stationNodeListPtr == NULL)
	{
		return NULL;
	}

	StationListNode* tmpPtr = stationNodeListPtr;

	for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		StationNode* stationNode = tmpPtr->stationNode;
		
		if(stationNode != NULL &&
				stationNode->thisStationID == thisStationID)
		{
			return stationNode;
		}
	}

	return NULL;
}

void removeStationNodeWithStationID0(int thisStationID)
{
	removeStationNodeWithStationID1(&mStationNodeListHead, thisStationID);
}

void removeStationNodeWithStationID1(
		StationListNode** stationNodeListPtrPtr,
		int thisStationID)
{
	if(stationNodeListPtrPtr == NULL ||
			(stationNodeListPtrPtr != NULL && *stationNodeListPtrPtr == NULL))
	{
		return;
	}

	StationListNode* tmpPtr = *stationNodeListPtrPtr;

	for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		StationNode* stationNode = tmpPtr->stationNode;
		
		if(stationNode != NULL &&
				stationNode->thisStationID == thisStationID)
		{
			if(tmpPtr->pre == NULL)
			{
				*stationNodeListPtrPtr = (*stationNodeListPtrPtr)->next;

				(*stationNodeListPtrPtr)->pre = NULL;

				free(tmpPtr);
			}
			else if(tmpPtr->next == NULL)
			{
				StationListNode* needRemoveNodePtr = tmpPtr;

				tmpPtr->pre->next = NULL;

				free(needRemoveNodePtr);
			}
			else
			{
				StationListNode* needRemoveNodePtr = tmpPtr;

				tmpPtr->pre->next = tmpPtr->next;

				tmpPtr->next->pre = tmpPtr->pre;

				free(needRemoveNodePtr);
			}

			break;
		}
	}
}

int addToStationPara0(
		int thisStationID,
		int toStationID,
		int toStationDistance)
{
	return addToStationPara2(
			mStationNodeListHead,
			thisStationID,
			toStationID,
			toStationDistance,
			NULL);
}

int addToStationPara1(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID,
		int toStationDistance)
{
	return addToStationPara2(
			stationNodeListPtr,
			thisStationID,
			toStationID,
			toStationDistance,
			NULL);
}

int addToStationPara2(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID,
		int toStationDistance,
		void* extraData)
{
	if(toStationDistance < 0)
	{
		return ERouteMgrError.EParaIllegal;
	}

	StationNode* stationNode = getStationNode(stationNodeListPtr, thisStationID);

	if(stationNode == NULL)
	{
		return ERouteMgrError.EStationNodeNotExist;
	}
	else
	{
		if(stationNode->toStationList == NULL)
		{
			stationNode->toStationList = (ToStationDataListNode*)malloc(sizeof(ToStationDataListNode));

			ToStationData* toStationData = (ToStationData*)malloc(sizeof(ToStationData));

			toStationData->toStationID = toStationID;

			toStationData->toStationDistance = toStationDistance;

			toStationData->extraData = extraData;

			stationNode->toStationList->toStationData = toStationData;

			stationNode->toStationList->pre = NULL;

			stationNode->toStationList->next = NULL;
		}
		else
		{
			ToStationDataListNode* tmpPtr = stationNode->toStationList;

			for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{
				if(tmpPtr->toStationData != NULL &&
						tmpPtr->toStationData->toStationID == toStationID)
				{
					return ERouteMgrError.EStationNodeToStationNodeExisted;
				}
				else if(tmpPtr->next == NULL)
				{
					ToStationData* toStationData =
							(ToStationData*)malloc(sizeof(ToStationData));

					toStationData->toStationID = toStationID;

					toStationData->toStationDistance = toStationDistance;

					toStationData->extraData = extraData;

					ToStationDataListNode* toStationListNode =
							(ToStationDataListNode*)malloc(sizeof(ToStationDataListNode));

					toStationListNode->toStationData = toStationData;

					toStationListNode->next = NULL;

					toStationListNode->pre = tmpPtr;

					tmpPtr->next = toStationListNode;

					tmpPtr = tmpPtr->next;

					break;
				}
			}
		}
	}

	return ERouteMgrError.ESuccess;
}

ToStationData* getToStationData0(
		int thisStationID,
		int toStationID)
{
	return getToStationData1(
			mStationNodeListHead,
			thisStationID,
			toStationID);
}

ToStationData* getToStationData1(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID)
{
	StationNode* stationNode = getStationNode(stationNodeListPtr, thisStationID);

	if(stationNode != NULL)
	{
		if(stationNode->toStationList == NULL)
		{
			return NULL;
		}
		
		ToStationDataListNode* tmpPtr = stationNode->toStationList;

		for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			ToStationData* toStationData = tmpPtr->toStationData;

			if(toStationData != NULL &&
					toStationData->toStationID == toStationID)
			{
				return toStationData;
			}
		}
	}

	return NULL;
}

StationListNode* getToStationList(
		StationListNode* stationNodeListPtr,
		int thisStationID)
{
	if(stationNodeListPtr == NULL)
	{
		return NULL;
	}

	StationListNode* resultStationNodeListHead = NULL;

	StationListNode* resultStationNodeListPtr = NULL;

	for(; stationNodeListPtr != NULL; stationNodeListPtr = stationNodeListPtr->next)
	{
		StationNode* stationNode = stationNodeListPtr->stationNode;

		if(stationNode != NULL &&
				stationNode->thisStationID != thisStationID)
		{
			continue;
		}

		if(stationNode != NULL &&
				stationNode->toStationList == NULL)
		{
			continue;
		}

		ToStationDataListNode* tmpPtr = stationNode->toStationList;

		for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			int toStationID = tmpPtr->toStationData->toStationID;

			StationNode* toStationNode = getStationNode(stationNodeListPtr, toStationID);

			if(toStationNode == NULL)
			{
				continue;
			}
			
			if(resultStationNodeListHead == NULL)
			{
				resultStationNodeListHead = (StationListNode*)malloc(sizeof(StationListNode));

				StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

				stationListNode->stationNode = toStationNode;

				stationListNode->next = NULL;

				stationListNode->pre = NULL;

				resultStationNodeListHead = stationListNode;

				resultStationNodeListPtr = resultStationNodeListHead;
			}
			else
			{
				bool isStationNodexExisted = false;

				StationListNode* subTmpPtr = resultStationNodeListHead;

				for(; subTmpPtr != NULL; subTmpPtr = subTmpPtr->next)
				{
					StationNode* tmpSubStationNode = subTmpPtr->stationNode;
					
					if(tmpSubStationNode != NULL &&
							tmpSubStationNode->thisStationID == stationNode->thisStationID)
					{
						isStationNodexExisted = true;

						break;
					}
				}

				if(!isStationNodexExisted)
				{
					StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

					stationListNode->stationNode = toStationNode;

					stationListNode->next = NULL;

					stationListNode->pre = resultStationNodeListPtr;

					resultStationNodeListPtr->next = stationListNode;

					resultStationNodeListPtr = resultStationNodeListPtr->next;
				}
			}
		}
	}

	return resultStationNodeListHead;
}

int getToStationDistance(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int endStationID)
{
	if(thisStationID == endStationID)
	{
		return 0;
	}

	if(stationNodeListPtr == NULL)
	{
		return 0;
	}

	for(; stationNodeListPtr != NULL; stationNodeListPtr = stationNodeListPtr->next)
	{
		StationNode* stationNode = stationNodeListPtr->stationNode;

		if(stationNode == NULL)
		{
			continue;
		}

		if(stationNode->thisStationID != thisStationID)
		{
			continue;
		}

		if(stationNode->toStationList == NULL)
		{
			continue;
		}
		
		ToStationDataListNode* tmpPtr = stationNode->toStationList;

		for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			ToStationData* toStationData = tmpPtr->toStationData;
			
			if(toStationData != NULL &&
					toStationData->toStationID == endStationID)
			{
				return toStationData->toStationDistance;
			}
		}
	}

	return 0;
}

void removeToStation0(
		int thisStationID,
		int toStationID)
{
	removeToStation1(
			mStationNodeListHead,
			thisStationID,
			toStationID);
}

void removeToStation1(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID)
{
	StationNode* stationNode = getStationNode(stationNodeListPtr, thisStationID);

	if(stationNode != NULL)
	{
		if(stationNode->toStationList == NULL)
		{
			return;
		}

		ToStationDataListNode* tmpPtr = stationNode->toStationList;

		for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			ToStationData* toStationData = tmpPtr->toStationData;
			
			if(toStationData != NULL &&
					toStationData->toStationID == toStationID)
			{
				ToStationDataListNode* toStationListNode = tmpPtr;

				if(tmpPtr->pre == NULL)
				{
					tmpPtr = tmpPtr->next;

					if(tmpPtr != NULL)
					{
						tmpPtr->pre = NULL;
					}
				}
				else if(tmpPtr->next == NULL)
				{
					tmpPtr = tmpPtr->pre;

					if(tmpPtr != NULL)
					{
						tmpPtr->next = NULL;
					}
				}
				else
				{
					tmpPtr->next->pre = tmpPtr->pre;

					tmpPtr->pre->next = tmpPtr->next;
				}
				
				free(toStationListNode);

				break;
			}
		}
	}
}

RouteListNode* getRoutes0(int startStationID, int endStationID)
{
	RouteListNode* resultRouteList =
			getRoute(
					mStationNodeListHead,
					startStationID,
					endStationID,
					0,
					NULL);

	return resultRouteList;
}

RouteListNode* getRoutes1(
		StationListNode* stationNodeListPtr,
		int startStationID,
		int endStationID)
{
	RouteListNode* resultRouteList =
			getRoute(
					stationNodeListPtr,
					startStationID,
					endStationID,
					0,
					NULL);

	return resultRouteList;
}

//core algorithm
RouteListNode* getRoute(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int endStationID,
		int currentRouteID,
		StationListNode* stationStack)
{
	if(thisStationID == endStationID)
	{
		return NULL;
	}

	if(stationNodeListPtr == NULL)
	{
		return NULL;
	}

	StationNode* thisStationNode = getStationNode(stationNodeListPtr, thisStationID);

	if(thisStationNode == NULL)
	{
		return NULL;
	}

	StationNode* endStationNode = getStationNode(stationNodeListPtr, endStationID);

	if(endStationNode == NULL)
	{
		return NULL;
	}

	StationListNode* toStationNodeList = getToStationList(stationNodeListPtr, thisStationID);

	if(toStationNodeList == NULL)
	{
		return NULL;
	}

	RouteListNode* resultRouteListHead = NULL;

	RouteListNode* resultRouteListPtr = NULL;

	if(stationStack == NULL)
	{
		stationStack = (StationListNode*)malloc(sizeof(StationListNode));

		stationStack->stationNode = thisStationNode;

		stationStack->pre = NULL;

		stationStack->next = NULL;
	}
	else
	{
		StationListNode* stationStackPtr = stationStack;

		StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

		stationListNode->stationNode = thisStationNode;

		stationListNode->next = NULL;

		for(; stationStackPtr != NULL; stationStackPtr = stationStackPtr->next)
		{
			if(stationStackPtr->next == NULL)
			{
				stationListNode->pre = stationStackPtr;

				stationStackPtr->next = stationListNode;

				stationStackPtr = stationStackPtr->next;
			}
		}
	}

	int routeIndex = currentRouteID;

	for(; toStationNodeList != NULL; toStationNodeList = toStationNodeList->next)
	{
		StationNode* stationNode = toStationNodeList->stationNode;

		bool result = isStationInClosedCycleList(stationStack, stationNode);

		if(result)
		{
			continue;
		}
		
		if(stationStack == NULL)
		{
			stationStack = (StationListNode*)malloc(sizeof(StationListNode));

			stationStack->stationNode = thisStationNode;

			stationStack->pre = NULL;

			stationStack->next = NULL;
		}
		else
		{
			StationListNode* stationStackPtr = stationStack;

			StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

			stationListNode->stationNode = thisStationNode;

			stationListNode->next = NULL;

			for(; stationStackPtr != NULL; stationStackPtr = stationStackPtr->next)
			{
				if(stationStackPtr->next == NULL)
				{
					stationListNode->pre = stationStackPtr;

					stationStackPtr->next = stationListNode;

					stationStackPtr = stationStackPtr->next;
				}
			}
		}
		
		if(stationNode->thisStationID == endStationID)
		{
			RouteData* resultRouteData = (RouteData*)malloc(sizeof(RouteData));

			//
			resultRouteData->stationList = (StationListNode*)malloc(sizeof(StationListNode));

			resultRouteData->stationList->pre = NULL;

			resultRouteData->stationList->stationNode = stationNode;

			resultRouteData->stationList->next = NULL;
			//

			resultRouteData->routeID = routeIndex++;

			if(resultRouteListHead == NULL)
			{
				resultRouteListHead = (RouteListNode*)malloc(sizeof(RouteListNode));

				resultRouteListHead->routeData = resultRouteData;

				resultRouteListHead->pre = NULL;

				resultRouteListHead->next = NULL;

				resultRouteListPtr = resultRouteListHead;
			}
			else
			{
				RouteListNode* routeListNode = (RouteListNode*)malloc(sizeof(RouteListNode));

				routeListNode->routeData = resultRouteData;

				routeListNode->next = NULL;

				routeListNode->pre = resultRouteListPtr;

				resultRouteListPtr->next = routeListNode;

				resultRouteListPtr = resultRouteListPtr->next;
			}
		}
		else
		{
			RouteListNode* tmpResultRouteList =
					getRoute(
							stationNodeListPtr,
							stationNode->thisStationID,
							endStationID,
							routeIndex,
							stationStack);
			
			if(tmpResultRouteList != NULL)
			{
				for(; tmpResultRouteList != NULL; tmpResultRouteList = tmpResultRouteList->next)
				{
					RouteData* resultRouteData = tmpResultRouteList->routeData;

					if(resultRouteData != NULL && resultRouteData->stationList != NULL)
					{
						resultRouteData->routeID = routeIndex;

						StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

						stationListNode->stationNode = stationNode;

						resultRouteData->stationList->pre = stationListNode;

						stationListNode->next = resultRouteData->stationList;

						stationListNode->pre = NULL;

						if(resultRouteListHead == NULL)
						{
							resultRouteListHead = (RouteListNode*)malloc(sizeof(RouteListNode));

							resultRouteListHead->routeData = resultRouteData;

							resultRouteListHead->pre = NULL;

							resultRouteListHead->next = NULL;

							resultRouteListPtr = resultRouteListHead;
						}
						else
						{
							RouteListNode* routeListNode = (RouteListNode*)malloc(sizeof(RouteListNode));

							routeListNode->routeData = resultRouteData;

							routeListNode->next = NULL;

							routeListNode->pre = resultRouteListPtr;

							resultRouteListPtr->next = routeListNode;

							resultRouteListPtr = resultRouteListPtr->next;
						}
					}
				}

				routeIndex++;
			}
			else
			{
				routeIndex--;
			}
		}
		
		if(stationStack != NULL)
		{
			StationListNode* tmpPtr = stationStack;

			for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{
				if(tmpPtr->next == NULL)
				{
					StationListNode* needRemoveStationListNode = tmpPtr;

					if(tmpPtr->pre == NULL)
					{
						stationStack = NULL;
					}

					free(needRemoveStationListNode);

					break;
				}
			}
		}
	}

	if(stationStack != NULL)
	{
		StationListNode* tmpPtr = stationStack;

		for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			if(tmpPtr->next == NULL)
			{
				StationListNode* needRemoveStationListNode = tmpPtr;

				if(tmpPtr->pre == NULL)
				{
					stationStack = NULL;
				}

				free(needRemoveStationListNode);

				break;
			}
		}
	}

	if(resultRouteListHead != NULL)
	{
		if(stationStack != NULL)
		{
			RouteListNode* tmpPtr = resultRouteListHead;

			for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{
				RouteData* routeData = tmpPtr->routeData;

				if(routeData != NULL && routeData->stationList != NULL)
				{
					StationListNode* stationListNode = (StationListNode*)malloc(sizeof(StationListNode));

					stationListNode->stationNode = thisStationNode;

					stationListNode->pre = NULL;

					routeData->stationList->pre = stationListNode;

					stationListNode->next = routeData->stationList;
				}
			}

			tmpPtr = resultRouteListHead;

			for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{
				RouteData* routeData = tmpPtr->routeData;

				StationListNode* stationList = routeData->stationList;

				if(stationList != NULL)
				{
					StationListNode* stationListNode = stationList;

					for(; stationListNode != NULL; stationListNode = stationListNode->next)
					{
						if(stationListNode->next != NULL)
						{
							StationNode* startStationNode = stationListNode->stationNode;

							StationNode* toStationNode = stationListNode->next->stationNode;

							if(startStationNode != NULL && toStationNode != NULL)
							{
								routeData->totalLength +=
										getToStationDistance(
												stationList,
												startStationNode->thisStationID,
												toStationNode->thisStationID);
							}
						}
						else
						{
							break;
						}
					}
				}
			}
		}
	}

	return resultRouteListHead;
}

bool isStationInClosedCycleList(
		StationListNode* srcStationNodeListPtr,
		StationNode* srcStationNode)
{
	if(srcStationNodeListPtr != NULL &&
			srcStationNode != NULL)
	{
		StationListNode* tmpPtr = srcStationNodeListPtr;

		for(; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			StationNode* stationNode = tmpPtr->stationNode;

			if(stationNode != NULL &&
					stationNode->thisStationID == srcStationNode->thisStationID)
			{
				return true;
			}
		}
	}

	return false;
}
