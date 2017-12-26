// Copyright. Aaron Cayabyab 2017.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public:
	UMainMenu();

	void SetServerList(TArray<FServerData> ServerNames);

	void SelectIndex(uint32 Index);

protected:
	
	virtual bool Initialize() override;

private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	//General
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void QuitGame();

	//Main Menu
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UFUNCTION()
	void OpenHostMenu();
	UFUNCTION()
	void OpenJoinMenu();

	//Join Menu
	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinMenuButton;
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;

	UFUNCTION()
	void JoinServer();


	//Host Menu
	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* ServerHostName;
	UPROPERTY(meta = (BindWidget))
	class UButton* CancelHostMenuButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* HostServerButton;

	UFUNCTION()
	void HostServer();

	TOptional<uint32> SelectedIndex;

	void UpdateChildren();
	
};
