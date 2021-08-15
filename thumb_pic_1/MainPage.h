#pragma once

#include "MainPage.g.h"
#include "thumbViewModel.h"

namespace winrt::thumb_pic_1::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> ThumbViewModelVec() const
        {
            return thumbViewModelVec;
        }

        //最初にやること（サムネイル画像を集める）
        Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs);

        //ここで、StorageFile、サムネイル画像、ファイル名を集めるよ
        Windows::Foundation::IAsyncAction AppendViewModelAsync();        

        //サムネイル画像を取得するよ
        Windows::Foundation::IAsyncOperation<Windows::UI::Xaml::Media::Imaging::BitmapImage> GetThumbnailAsync(Windows::Storage::StorageFile m_imageFile);

    private:
        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> thumbViewModelVec{ nullptr };

    };
}

namespace winrt::thumb_pic_1::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
