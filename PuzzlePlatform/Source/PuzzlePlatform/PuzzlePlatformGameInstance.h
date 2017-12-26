// Aaron Cayabyab 2017.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformGameInstance	(const FObjectInitializer & ObjectInitializer);
	
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadStartMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	virtual void Host() override;

	UFUNCTION(Exec)
	virtual void Join(uint32 Index) override;

	UFUNCTION(Exec)
	virtual void LoadMainMenu() override;

	virtual void RefreshServerList() override;


private:
	 TSubclassOf<class UUserWidget> MenuClass;
	 TSubclassOf<class UUserWidget> InGameMenuClass;

	 class UMainMenu* Menu;
	 class UInGameMenu* InGameMenu;

	 IOnlineSessionPtr SessionInterface;
	 TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	 void OnCreateSessionComplete(FName SessionName, bool Success);
	 void OnDestroySessionComplete(FName SessionName, bool Success);
	 void OnFindSessionsComplete(bool Success);
	 void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	 void CreateSession();
};
