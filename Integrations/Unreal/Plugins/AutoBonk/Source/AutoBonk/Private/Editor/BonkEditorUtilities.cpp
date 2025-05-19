// Copyright FTL Goats Interactive LLC

#include "Editor/BonkEditorUtilities.h"

#if WITH_EDITOR
#include "ContentBrowserModule.h"
#include "ContentBrowserDataSubsystem.h"
#include "IContentBrowserSingleton.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#endif

#if WITH_EDITOR
void UBonkEditorUtilities::SyncBrowserToItems(const TArray<FString>& ItemList)
{
	if (!IsValid(GEditor))
	{
		return;
	}

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	TArray<FContentBrowserItem> AsBrowserItems;
	if (UContentBrowserDataSubsystem* ContentBrowserData = GEditor->GetEditorSubsystem<UContentBrowserDataSubsystem>())
	{
		for (const FString& Item : ItemList)
		{
			FString FinalItem = Item;
			// Unreal has trouble dealing with a trailing slash... so remove it.
			if (FinalItem.EndsWith(TEXT("/")))
			{
				FinalItem = FinalItem.LeftChop(1);
			}
			bool bFoundSomething = false;
			
			// Try to find the package directly. If it is /Game/Object, we want /Game/Object.Object or else GetItemAtPath() will not work.
			// So use the AssetRegistry to help us make that path for us.
			{
				TArray<FAssetData> AssetData;
				if (!FinalItem.IsEmpty())
				{
					const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
					AssetRegistryModule.Get().GetAssetsByPackageName(FName(*FinalItem), AssetData, true, false);
				}

				for (const FAssetData& AssetDatum : AssetData)
				{
					if (!(AssetDatum.IsUAsset() && AssetDatum.IsTopLevelAsset()))
					{
						continue;
					}

					FString AssetPath = FSoftObjectPath(AssetDatum.GetAsset()).GetAssetPath().ToString();
					FName AsVirtual = FName(AssetPath);
					ContentBrowserData->Legacy_TryConvertAssetDataToVirtualPaths(AssetDatum, false, [&](FName VirtualPath) -> bool {
						AsVirtual = VirtualPath;
						return true;
					});
					AsBrowserItems.Add(ContentBrowserData->GetItemAtPath(AsVirtual, EContentBrowserItemTypeFilter::IncludeAll));
					bFoundSomething = true;
				}
			}

			// If we didn't find anything, then treat it as a generic folder and use that to sync.
			if (!bFoundSomething)
			{
				FName AsVirtual = FName(FinalItem);
				ContentBrowserData->Legacy_TryConvertPackagePathToVirtualPaths(FName(FinalItem), [&](FName VirtualPath) -> bool {
					AsVirtual = VirtualPath;
					return true;
				});
				AsBrowserItems.Add(ContentBrowserData->GetItemAtPath(AsVirtual, EContentBrowserItemTypeFilter::IncludeAll));
			}
		}
	}
	
	ContentBrowserModule.Get().SyncBrowserToItems(AsBrowserItems, false, true);
}
#endif
