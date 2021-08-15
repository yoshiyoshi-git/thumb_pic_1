#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.Storage.Search.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::thumb_pic_1::implementation
{
    MainPage::MainPage()
    {
        thumbViewModelVec = winrt::single_threaded_observable_vector<IInspectable>();
        InitializeComponent();
    }
    
    //AppendViewModelAsync()を呼ぶだけ
    Windows::Foundation::IAsyncAction MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs)
    {
        if (ThumbViewModelVec().Size() == 0)
            co_await AppendViewModelAsync();
    }
    

    Windows::Foundation::IAsyncAction MainPage::AppendViewModelAsync()
    {
        //サーチするのは「jpg」「png」「gif」
        Windows::Storage::Search::QueryOptions searchoptions{};
        searchoptions.FolderDepth(Windows::Storage::Search::FolderDepth::Deep);
        searchoptions.FileTypeFilter().Append(L".jpg");
        searchoptions.FileTypeFilter().Append(L".png");
        searchoptions.FileTypeFilter().Append(L".gif");

        //ピクチャーフォルダをサーチ
        Windows::Storage::StorageFolder picturesfolder = Windows::Storage::KnownFolders::PicturesLibrary();

        //上記の条件に合うのを探す
        auto searchresult = picturesfolder.CreateFileQueryWithOptions(searchoptions);
        auto imagefiles = co_await searchresult.GetFilesAsync();

        //StorageFileからサムネイル画像とファイル名を取得して、ThumbViewModelを作成し、ThumbViewModelVecへAppend（追加）
        for (auto&& file : imagefiles)
        {
            if (file.Provider().Id() == L"computer")
            {
                auto thumbimage = co_await GetThumbnailAsync(file);
                auto thumbview = winrt::make<thumbViewModel>(file, thumbimage, file.DisplayName());
                ThumbViewModelVec().Append(thumbview);
            }
        }
    }
    //GetThumbnailAsyncは右の定義　IAsyncOperation<StorageItemThumbnail> GetThumbnailAsync(ThumbnailMode const& mode);
    //IAsyncOperation型はco_awaitを使用して呼び出すと、テンプレートパラメータの型を返す。
    //なのでco_await imagefile.GetThumbnailAsync()はStorageItemThumbnail型を返すよ。
    //と言うわけで、GetThumbnailAsync()はco_awaitを使用して呼び出すとBitmapImageを返すよ。
    Windows::Foundation::IAsyncOperation<Windows::UI::Xaml::Media::Imaging::BitmapImage> MainPage::GetThumbnailAsync(Windows::Storage::StorageFile imagefile)
    {
        auto thumbnail = co_await imagefile.GetThumbnailAsync(Windows::Storage::FileProperties::ThumbnailMode::PicturesView);
        Windows::UI::Xaml::Media::Imaging::BitmapImage thumbnailimage{};
        thumbnailimage.SetSource(thumbnail);
        thumbnail.Close();

        co_return thumbnailimage;
    }
}
