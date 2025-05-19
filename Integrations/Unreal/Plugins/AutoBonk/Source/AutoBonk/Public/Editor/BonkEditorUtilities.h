// Copyright FTL Goats Interactive LLC

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "BonkEditorUtilities.generated.h"

// Expose editor utility functions to Blutilities  in addition to UEditorUtilityLibrary
UCLASS()
class AUTOBONK_API UBonkEditorUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	/**
	 * Sync the Content Browser to the given item(s)
	 * @param	ItemList	The list of items to sync to in the Content Browser
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Content Browser")
	static void SyncBrowserToItems(const TArray<FString>& ItemList);
#endif
};
