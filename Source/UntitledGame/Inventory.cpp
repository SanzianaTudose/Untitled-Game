// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(int Slot, AActor* Item)
{
    if (Items.Num() < MaxItems)
    {
        Items.Add(Item);
    }
}

void Inventory::RemoveItem(int Slot)
{
    if (Items.Num() > 0)
    {
        Items.RemoveAt(Slot, 1, true);
    }
}

AActor* Inventory::QueryItem(int Slot)
{
    if (Items.Num() > 0)
    {
        return Items[Slot];
    }
    return nullptr;
}


