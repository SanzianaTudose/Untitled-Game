#include "Inventory.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Component.h"


UInventory::UInventory()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UInventory::AddItem(UDataAsset* Item)
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

UDataAsset* UInventory::QueryItem(int Slot)
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
            UHorizontalBox* HorizontalBox = Cast<UHorizontalBox>(InventoryUI->WidgetTree->FindWidget("InventoryBox"));
            
            if (HorizontalBox)
            {
                UE_LOG(LogTemp, Warning, TEXT("HorizontalBox found!"));
                
                // Clear the existing widgets in the HorizontalBox
                HorizontalBox->ClearChildren();

                // Repopulate the HorizontalBox with current items
                for (UDataAsset* Item : Items)
                {
                    UUserWidget* ItemWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ItemWidget);
                    if (ItemWidgetInstance)
                    {
                        UComponent* AsComponent = Cast<UComponent>(Item);
                        // if (AsComponent)
                        // {
                        //     UImage* ItemImage = Cast<UImage>(ItemWidgetInstance->WidgetTree->FindWidget("ItemImage"));
                        //     if (ItemImage)
                        //     {
                        //         // ItemImage->SetBrushFromTexture(IconMap[AsComponent->Type]);
                        //     }
                        // }
                        HorizontalBox->AddChildToHorizontalBox(ItemWidgetInstance);
                    }
                }
            }
        }
    }
}