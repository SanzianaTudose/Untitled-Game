// Fill out your copyright notice in the Description page of Project Settings.


#include "Component.h"

UComponent::UComponent()
{
    switch(componentType){
        case ComponentType::Stock:
            ItemType = TypeOfItem::Stock;
            break;
        case ComponentType::Barrel:
            ItemType = TypeOfItem::Barrel;
            break;
        case ComponentType::Sight:
            ItemType = TypeOfItem::Sight;
            break;
        case ComponentType::Trigger:
            ItemType = TypeOfItem::Trigger;
            break;

    }
}

