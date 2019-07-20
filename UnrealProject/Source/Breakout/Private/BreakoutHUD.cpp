// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakoutHUD.h"
#include "Blueprint/UserWidget.h"
#include "ConstructorHelpers.h"

ABreakoutHUD::ABreakoutHUD()
{
    //WidgetBlueprint'/Game/Blueprints/UI/GameUI.GameUI'
    static ConstructorHelpers::FClassFinder<UUserWidget>playerHud(TEXT("/Game/Blueprints/UI/GameUI"));
    if (playerHud.Succeeded())
        PlayerGuiClass = playerHud.Class;
}
void ABreakoutHUD::BeginPlay()
{
    Super::BeginPlay();
    PlayerGui = CreateWidget<UUserWidget>(GetGameInstance(),PlayerGuiClass);
    PlayerGui->AddToViewport();

}
