// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerSessionsSubsystem.generated.h"

//
//
//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayOnDestroySessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayOnStartSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSION_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UMultiplayerSessionsSubsystem();

	//
	// menu��������º����������Ự��
	//
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSession(int32 MaxSearchResult);
	void JoinSession(const FOnlineSessionSearchResult& SearchResult);
	void DestroyGameSession();
	void StartGameSession();

	//
	// 自定义委托
	//
	FMultiplayOnCreateSessionComplete MultiplayOnCreateSessionComplete;
	FMultiplayOnDestroySessionComplete MultiplayOnDestroySessionComplete;
	FMultiplayOnStartSessionComplete MultiplayOnStartSessionComplete;
	FMultiplayOnFindSessionsComplete MultiplayOnFindSessionsComplete;
	FMultiplayOnJoinSessionComplete MultiplayOnJoinSessionComplete;
	
private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	//
	//���±���������ί�У��Է����ڶ���ί��ʱ�����ص�����
	//
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;

	//
	//���±���������ί�о�����Է����ڻص�ʱ����ί��
	//
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	FDelegateHandle StartSessionCompleteDelegateHandle;
	
	bool bCreateSessionOnDestroy{false};
	int32 LastNumPublicConnections;
	FString LastMatchType;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
protected:
	
	//
	//绑定委托的函数
	//
	void OnCreateSessionCompleteDelegate(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsCompleteDelegate(bool bWasSuccessful);
	void OnJoinSessionCompleteDelegate(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionCompleteDelegate(FName SessionName, bool bWasSuccessful);
	void OnStartSessionCompleteDelegate(FName SessionName, bool bWasSuccessful);

	
	//
	//�Զ���ί�еĻص�
	//
	void OnCreateSession(bool bWasSuccessful);

};
