#ifndef ROUTEPLANMANAGER_H
#define ROUTEPLANMANAGER_H

typedef enum bool
{
	false,
	true
}bool;

typedef struct _ERouteMgrError
{
	int ESuccess;

	int EStationNodeNotExist;

	int EStationNodeExisted;

	int EStationNodeToStationNodeExisted;

	int EParaIllegal;

	int EInternalError;
};

typedef struct ToStationData
{
	int toStationID;

	int toStationDistance;

	void* extraData;
}ToStationData;

typedef struct ToStationDataListNode
{
	ToStationData* toStationData;

	struct ToStationDataListNode* pre;

	struct ToStationDataListNode* next;
}ToStationDataListNode;

typedef struct StationNode
{
	int thisStationID;

	ToStationDataListNode* toStationList;

	void* extraData;
}StationNode;

typedef struct StationListNode
{
	StationNode* stationNode;

	struct StationListNode* pre;

	struct StationListNode* next;
}StationListNode;

typedef struct RouteData
{
	StationListNode* stationList;

	int routeID;

	int totalLength;
}RouteData;

typedef struct RouteListNode
{
	RouteData* routeData;

	struct RouteListNode* pre;

	struct RouteListNode* next;
}RouteListNode;

static struct _ERouteMgrError ERouteMgrError =
{
		0,
		1,
		2,
		3,
		4,
		5
};

//example data codes
void initTestStationList();

int addStationNode0(int stationID);

int addStationNode1(int stationID, void* extraData);

int addStationNode2(
		StationListNode* stationNodeListPtr,
		int stationID);

int addStationNode3(
		StationListNode* stationNodeListPtr,
		int stationID,
		void* extraData);

StationNode* getStationNode(
		StationListNode* stationNodeListPtr,
		int thisStationID);

void removeStationNodeWithStationID0(int thisStationID);

void removeStationNodeWithStationID1(
		StationListNode** stationNodeListPtrPtr,
		int thisStationID);

int addToStationPara0(
		int thisStationID,
		int toStationID,
		int toStationDistance);

int addToStationPara1(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID,
		int toStationDistance);

int addToStationPara2(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID,
		int toStationDistance,
		void* extraData);

ToStationData* getToStationData0(
		int thisStationID,
		int toStationID);

ToStationData* getToStationData1(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID);

static StationListNode* getToStationList(
		StationListNode* stationNodeListPtr,
		int thisStationID);

static int getToStationDistance(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int endStationID);

void removeToStation0(
		int thisStationID,
		int toStationID);

void removeToStation1(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int toStationID);

RouteListNode* getRoutes0(
		int startStationID,
		int endStationID);

RouteListNode* getRoutes1(
		StationListNode* stationNodeListPtr,
		int startStationID,
		int endStationID);

static RouteListNode* getRoute(
		StationListNode* stationNodeListPtr,
		int thisStationID,
		int endStationID,
		int currentRouteID,
		StationListNode* stackStationNodeListPtr);

static bool isStationInClosedCycleList(
		StationListNode* srcStationNodeListPtr,
		StationNode* srcStationNode);

#endif /*RoutePlanManager.h*/
