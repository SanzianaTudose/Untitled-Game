#include "Inventory.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Component.h"


UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventory::AddItem(int Slot, UComponent* Item)
{
    if (Items.Num() < MaxItems)
    {
        Items.Add(Item);
        DisplayInventory();
    }
}

void UInventory::RemoveItem(int Slot)
{
    if (Items.Num() > 0)
    {
        Items.RemoveAt(Slot, 1, true);
        DisplayInventory();
    }
}

UComponent* UInventory::QueryItem(int Slot)
{
    if (Items.Num() > 0)
    {
        return Items[Slot];
    }
    return nullptr;
}

void UInventory::DisplayInventory()
{
    if (InventoryWidget && ItemWidget)
    {
        UUserWidget* InventoryUI = CreateWidget<UUserWidget>(GetWorld(), InventoryWidget);
        if (InventoryUI)
        {
            InventoryUI->AddToViewport();

            // Find the HorizontalBox in your InventoryWidget
            UHorizontalBox* HorizontalBox = Cast<UHorizontalBox>(InventoryUI->WidgetTree->FindWidget("YourHorizontalBoxName"));
            
            if (HorizontalBox)
            {
                // Clear the existing widgets in the HorizontalBox
                HorizontalBox->ClearChildren();

                // Repopulate the HorizontalBox with current items
                for (UComponent* Item : Items)
                {
                    UUserWidget* ItemWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ItemWidget);
                    if (ItemWidgetInstance)
                    {
                        // Set the item image or other properties
                        // ...

                        HorizontalBox->AddChildToHorizontalBox(ItemWidgetInstance);
                    }
                }
            }
        }
    }
}