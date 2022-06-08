// Fill out your copyright notice in the Description page of Project Settings.


#include "MainViewModel.h"

#include "NoesisTypeClass.h"

UMainViewModel::UMainViewModel(const FObjectInitializer& ObjectInitializer)
{
    HUD = NewObject<UHUDViewModel>();
}

void UMainViewModel::ToggleMenu()
{
    Menu = Menu == nullptr ? NewObject<UMenuViewModel>() : nullptr;
    NoesisNotifyPropertyChanged(this, TEXT("Menu"));
}
