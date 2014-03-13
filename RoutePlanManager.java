/*
 * this java source file supply route plan algorithm
 * 
 * Description:
 * 1.support instantiate mode and singleton mode
 * 2.calculate route point from start to end
 * 3.supply core route plan algorithm with relate data
 * 
 * Usage:
 * 1.Instantiation:
 * RoutePlanManager rpMgr = new RoutePlanManager();
 * 2.singleton:
 * RoutePlanManager rpMgr = RoutePlanManager.getInstance();
 * 
 * rpMgr.initTestStationList();
 * 
 * ArrayList<RouteData> result = rpMgr.getRoutes(0, 1);
 * 
 * Author:
 * 
 * Zhang Xuyang
 * 
 * 20140-03-13
 */
package com.smit.Utility;

import java.util.ArrayList;

public class RoutePlanManager
{
	public enum ERouteMgrError
	{
		ESuccess,
		EStationNodeNotExist,
		EStationNodeExisted,
		EStationNodeToStationNodeExisted,
		EParaIllegal,
		EInternalError
	}
	
	public static class ToStationData
    {
    	public int toStationID;
    	
    	public int toStationDistance;
    	
    	public Object extraData;
    }
    
    private static class StationNode
    {
    	public int thisStationID;
    	
    	public ArrayList<ToStationData> toStationList;
    	
    	public Object extraData;
    }
    
    public static class RouteData
    {
    	public ArrayList<StationNode> stationList;
    	
    	public int routeID;
    	
    	public int totalLength;
    }
    
    public static RoutePlanManager mInstance;
    
    private ArrayList<StationNode> mStationNodeList;
    
    public RoutePlanManager()
    {
    	super();
    }
    
    public static RoutePlanManager getInstance()
    {
    	if(mInstance == null)
    	{
    		mInstance = new RoutePlanManager();
    	}
    	
    	return mInstance;
    }
    
    //example data codes
    public void initTestStationList()
    {
		//A
    	addStationNode(0);
    	
		//AB
    	addToStationPara(0, 1, 5);
		
		//AD
    	addToStationPara(0, 3, 5);
		
		//AE
    	addToStationPara(0, 4, 7);
		
		//B
    	addStationNode(1);
		
		//BC
    	addToStationPara(1, 2, 4);
		
		//C
    	addStationNode(2);
		
		//CD
    	addToStationPara(2, 3, 8);
		
		//CE
    	addToStationPara(2, 4, 2);
		
		//D
    	addStationNode(3);
		
		//DC
    	addToStationPara(3, 2, 8);
		
		//DE
    	addToStationPara(3, 4, 6);
		
		//E
    	addStationNode(4);
		
		//EB
    	addToStationPara(4, 1, 3);
    }
    
    public ERouteMgrError addStationNode(int stationID)
    {
    	return addStationNode(
    			mStationNodeList, 
    			stationID, 
    			null);
    }
    
    public ERouteMgrError addStationNode(int stationID, Object extraData)
    {
    	return addStationNode(
    			mStationNodeList, 
    			stationID, 
    			extraData);
    }
    
    public ERouteMgrError addStationNode(
    		ArrayList<StationNode> stationNodeList, 
    		int stationID)
    {
    	return addStationNode( 
    			stationNodeList, 
    			stationID, 
    			null);
    }
    
    public ERouteMgrError addStationNode(
    		ArrayList<StationNode> stationNodeList, 
    		int stationID, 
    		Object extraData)
    {
    	if(stationNodeList == null)
    	{
	    	if(mStationNodeList == null)
	    	{
	    		mStationNodeList = new ArrayList<StationNode>();
	    	}
	    	
	    	stationNodeList = mStationNodeList;
    	}
    	
    	StationNode stationNode = getStationNode(stationNodeList, stationID);
    	
    	if(stationNode == null)
    	{
    		stationNode = new StationNode();
    		
    		stationNode.thisStationID = stationID;
    		
    		stationNode.extraData = extraData;
    		
    		stationNodeList.add(stationNode);
    	}
    	else
    	{
    		return ERouteMgrError.EStationNodeExisted;
    	}
    	
    	return ERouteMgrError.ESuccess;
    }
    
    public static StationNode getStationNode(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID)
    {
    	if(stationNodeList == null)
    	{
    		return null;
    	}
    	
    	for(int i = 0; i < stationNodeList.size(); i++)
    	{
    		StationNode stationNode = stationNodeList.get(i);
    		
    		if(stationNode.thisStationID == thisStationID)
    		{
    			return stationNode;
    		}
    	}
    	
    	return null;
    }
    
    public void removeStationNodeWithStationID(int thisStationID)
    {
    	removeStationNodeWithStationID(mStationNodeList, thisStationID);
    }
    
    public void removeStationNodeWithStationID(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID)
    {
    	if(stationNodeList == null)
    	{
    		return;
    	}
    	
    	for(int i = 0; i < stationNodeList.size(); i++)
    	{
    		StationNode stationNode = stationNodeList.get(i);
    		
    		if(stationNode.thisStationID == thisStationID)
    		{
    			stationNodeList.remove(i);
    			
    			break;
    		}
    	}
    }

    public ERouteMgrError addToStationPara(
    		int thisStationID, 
    		int toStationID, 
    		int toStationDistance)
    {
    	return addToStationPara(
    			mStationNodeList, 
    			thisStationID, 
    			toStationID, 
    			toStationDistance, 
    			null);
    }
    
    public ERouteMgrError addToStationPara(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID, 
    		int toStationID, 
    		int toStationDistance)
    {
    	return addToStationPara(
        		stationNodeList, 
        		thisStationID, 
        		toStationID, 
        		toStationDistance, 
        		null);
    }
    
    public ERouteMgrError addToStationPara(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID, 
    		int toStationID, 
    		int toStationDistance, 
    		Object extraData)
    {
    	if(toStationDistance < 0)
    	{
    		return ERouteMgrError.EParaIllegal;
    	}
    	
    	StationNode stationNode = getStationNode(stationNodeList, thisStationID);
    	
    	if(stationNode == null)
    	{
    		return ERouteMgrError.EStationNodeNotExist;
    	}
    	else
    	{
    		if(stationNode.toStationList == null)
    		{
    			stationNode.toStationList = new ArrayList<ToStationData>();
    		}
    		
    		for(int i = 0; i < stationNode.toStationList.size(); i++)
    		{
    			ToStationData toStationData = stationNode.toStationList.get(i);
    			
    			if(toStationData.toStationID == toStationID)
    			{
    				return ERouteMgrError.EStationNodeToStationNodeExisted;
    			}
    		}
    		
    		ToStationData toStationData = new ToStationData();
    		
    		toStationData.toStationID = toStationID;
    		
    		toStationData.toStationDistance = toStationDistance;
    		
    		toStationData.extraData = extraData;
    		
    		stationNode.toStationList.add(toStationData);
    	}
    	
    	return ERouteMgrError.ESuccess;
    }
    
    public ToStationData getToStationData(
    		int thisStationID, 
    		int toStationID)
    {
    	return getToStationData(
    			mStationNodeList, 
    			thisStationID, 
    			toStationID);
    }
    
    public ToStationData getToStationData(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID, 
    		int toStationID)
    {
    	StationNode stationNode = getStationNode(stationNodeList, thisStationID);
    	
    	if(stationNode != null)
    	{
    		if(stationNode.toStationList == null)
    		{
    			return null;
    		}
    		
    		for(int i = 0; i < stationNode.toStationList.size(); i++)
    		{
    			ToStationData toStationData = stationNode.toStationList.get(i);
    			
    			if(toStationData.toStationID == toStationID)
    			{
    				return toStationData;
    			}
    		}
    	}
    	
    	return null;
    }
    
    private static ArrayList<StationNode> getToStationList(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID)
    {
    	if(stationNodeList == null)
    	{
    		return null;
    	}
    	
    	ArrayList<StationNode> resultStationNodeList = null;
    	
    	for(int i = 0; i < stationNodeList.size(); i++)
    	{
    		StationNode stationNode = stationNodeList.get(i);
    		
    		if(stationNode.thisStationID != thisStationID)
    		{
    			continue;
    		}
    		
			if(stationNode.toStationList == null)
			{
				continue;
			}
			
			for(int j = 0; j < stationNode.toStationList.size(); j++)
			{
				int toStationID = stationNode.toStationList.get(j).toStationID;
				
				StationNode toStationNode = getStationNode(stationNodeList, toStationID);
				
				if(toStationNode == null)
				{
					continue;
				}
				
				if(resultStationNodeList == null)
				{
					resultStationNodeList = new ArrayList<StationNode>();
				}
				
				boolean isStationNodexExisted = false;
				
				for(int k = 0; k < resultStationNodeList.size(); k++)
				{
					StationNode tmpSubStationNode = resultStationNodeList.get(k);
					
					if(tmpSubStationNode.thisStationID == stationNode.thisStationID)
					{
						isStationNodexExisted = true;
						
						break;
					}
				}
				
				if(!isStationNodexExisted)
				{
					resultStationNodeList.add(toStationNode);
				}
			}
    	}
    	
    	return resultStationNodeList;
    }
    
    private static int getToStationDistance(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID, 
    		int endStationID)
    {
    	if(thisStationID == endStationID)
    	{
    		return 0;
    	}
    	
		if(stationNodeList == null)
		{
			return 0;
		}
		
		for(int i = 0; i < stationNodeList.size(); i++)
		{
			StationNode stationNode = stationNodeList.get(i);
			
			if(stationNode.thisStationID != thisStationID)
			{
				continue;
			}
			
			if(stationNode.toStationList == null || 
					(stationNode.toStationList != null && stationNode.toStationList.size() <= 0))
			{
				continue;
			}
			
			for(int j = 0; j < stationNode.toStationList.size(); j++)
			{
				ToStationData toStationData = stationNode.toStationList.get(j);
				
				if(toStationData.toStationID == endStationID)
				{
					return toStationData.toStationDistance;
				}
			}
		}
    	
    	return 0;
    }
    
    public void removeToStation(
    		int thisStationID, 
    		int toStationID)
    {
    	removeToStation(
    			mStationNodeList, 
    			thisStationID, 
    			toStationID);
    }
    
    public void removeToStation(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID, 
    		int toStationID)
    {
    	StationNode stationNode = getStationNode(stationNodeList, thisStationID);
    	
    	if(stationNode != null)
    	{
    		if(stationNode.toStationList == null)
    		{
    			return;
    		}
    		
    		for(int i = 0; i < stationNode.toStationList.size(); i++)
    		{
    			ToStationData toStationData = stationNode.toStationList.get(i);
    			
    			if(toStationData.toStationID == toStationID)
    			{
    				stationNode.toStationList.remove(i);
    				
    				break;
    			}
    		}
    	}
    }
    
    public ArrayList<RouteData> getRoutes(int startStationID, int endStationID)
    {
    	ArrayList<RouteData> resultRouteList = 
    			getRoute(
    					mStationNodeList, 
    					startStationID, 
    					endStationID, 
    					0, 
    					null);
    	
    	return resultRouteList;
    }
    
    public static ArrayList<RouteData> getRoutes(
    		ArrayList<StationNode> stationNodeList, 
    		int startStationID, 
    		int endStationID)
    {
    	ArrayList<RouteData> resultRouteList = 
    			getRoute(
    					stationNodeList, 
    					startStationID, 
    					endStationID, 
    					0, 
    					null);
    	
    	return resultRouteList;
    }
    
    //core algorithm
    private static ArrayList<RouteData> getRoute(
    		ArrayList<StationNode> stationNodeList, 
    		int thisStationID, 
			int endStationID, 
    		int currentRouteID, 
    		ArrayList<StationNode> stationStack)
    {
    	if(thisStationID == endStationID)
    	{
    		return null;
    	}
    	
    	if(stationNodeList == null || 
    			(stationNodeList != null && stationNodeList.size() <= 0))
    	{
    		return null;
    	}
    	
    	StationNode thisStationNode = getStationNode(stationNodeList, thisStationID);
    	
    	if(thisStationNode == null)
    	{
    		return null;
    	}
    	
    	StationNode endStationNode = getStationNode(stationNodeList, endStationID);
    	
    	if(endStationNode == null)
    	{
    		return null;
    	}
    	
    	ArrayList<StationNode> toStationNodeList = getToStationList(stationNodeList, thisStationID);
    	
    	if(toStationNodeList == null || 
    			(toStationNodeList != null && toStationNodeList.size() <= 0))
    	{
    		return null;
    	}
    	
		ArrayList<RouteData> resultRouteList = null;
    	
		if(stationStack == null)
		{
			stationStack = new ArrayList<StationNode>();
		}
		
		stationStack.add(thisStationNode);
		
    	int routeIndex = currentRouteID;
    	
    	for(int i = 0; i < toStationNodeList.size(); i++)
    	{
    		StationNode stationNode = toStationNodeList.get(i);
    		
			boolean result = isStationInClosedCycleList(stationStack, stationNode);
			
			if(result)
			{
				continue;
			}
    		
    		stationStack.add(stationNode);
    		
    		if(stationNode.thisStationID == endStationID)
    		{
    			if(resultRouteList == null)
    			{
    				resultRouteList = new ArrayList<RouteData>();
    			}
    			
    			RouteData resultRouteData = new RouteData();
    			
    			resultRouteData.stationList = new ArrayList<StationNode>();
    			
    			resultRouteData.stationList.add(stationNode);
    			
    			resultRouteData.routeID = routeIndex++;
    			
    			resultRouteList.add(resultRouteData);
    		}
    		else
    		{
    			ArrayList<RouteData> tmpResultRouteList = 
    					getRoute(
    							stationNodeList, 
    							stationNode.thisStationID, 
    							endStationID, 
    							routeIndex, 
    							stationStack);
    			
    			if(tmpResultRouteList != null && 
    					tmpResultRouteList.size() > 0)
    			{
    				for(int j = 0; j < tmpResultRouteList.size(); j++)
    				{
    					RouteData resultRouteData = tmpResultRouteList.get(j);
    					
						if(resultRouteData.stationList != null && 
								resultRouteData.stationList.size() > 0)
						{
    						resultRouteData.routeID = routeIndex;
    						
    						resultRouteData.stationList.add(0, stationNode);
    						
    						if(resultRouteList == null)
    		    			{
    		    				resultRouteList = new ArrayList<RouteData>();
    		    			}
    						
    						resultRouteList.add(resultRouteData);
						}
    				}
    				
    				routeIndex++;
    			}
    			else
    			{
    				routeIndex--;
    			}
    		}
    		
    		if(stationStack.size() > 0)
    		{
    			stationStack.remove(stationStack.size() - 1);
    		}
    	}
		
		if(stationStack.size() > 0)
		{
			stationStack.remove(stationStack.size() - 1);
		}
    	
		if(resultRouteList != null)
		{
			if(stationStack != null && stationStack.size() == 0)
			{
				for(int i = 0; i < resultRouteList.size(); i++)
				{
					RouteData routeData = resultRouteList.get(i);
					
					if(routeData.stationList != null && 
							routeData.stationList.size() > 0)
					{
						routeData.stationList.add(0, thisStationNode);
					}
				}
				
				for(int i = 0; i < resultRouteList.size(); i++)
	    		{
	    			RouteData routeData = resultRouteList.get(i);
	    			
	    			ArrayList<StationNode> stationList = routeData.stationList;
	    			
	    			if(stationList != null && stationList.size() > 0)
	    			{
	    				for(int j = 0; j < stationList.size() - 1; j++)
	    				{
	    					StationNode startStationNode = stationList.get(j);
	    					
	    					StationNode toStationNode = stationList.get(j + 1);
	    					
	    					routeData.totalLength += 
	    							getToStationDistance(
	    									stationNodeList, 
	    									startStationNode.thisStationID, 
	    									toStationNode.thisStationID);
	    				}
	    			}
	    		}
			}
		}
		
    	return resultRouteList;
    }
    
    private static boolean isStationInClosedCycleList(
    		ArrayList<StationNode> srcStationNodeList, 
    		StationNode srcStationNode)
    {
    	if(srcStationNodeList != null && 
    			srcStationNode != null)
    	{
    		for(int i = 0; i < srcStationNodeList.size(); i++)
    		{
    			StationNode stationNode = srcStationNodeList.get(i);
    			
    			if(srcStationNode.thisStationID == stationNode.thisStationID)
    			{
    				return true;
    			}
    		}
    	}
    	
    	return false;
    }
}
