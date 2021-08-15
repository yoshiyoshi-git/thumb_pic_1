#pragma once

#include "thumbViewModel.g.h"

namespace winrt::thumb_pic_1::implementation
{
    struct thumbViewModel : thumbViewModelT<thumbViewModel>
    {
        thumbViewModel() = default;
        thumbViewModel(
            Windows::Storage::StorageFile const& imagefile,
            Windows::UI::Xaml::Media::Imaging::BitmapImage const& thumbimage,
            hstring const& imagename
        ) :
            imageFile(imagefile),
            thumbImage(thumbimage),
            imageName(imagename)
        {}

        Windows::Storage::StorageFile GetImageFile() const
        {
            return imageFile;
        }

        Windows::UI::Xaml::Media::Imaging::BitmapImage GetThumbImage() const
        {
            return thumbImage;
        }

        hstring GetImageName() const
        {
            return imageName;
        }


    private:
        Windows::Storage::StorageFile imageFile{ nullptr };
        Windows::UI::Xaml::Media::Imaging::BitmapImage thumbImage;
        hstring imageName;

    };
}

namespace winrt::thumb_pic_1::factory_implementation
{
    struct thumbViewModel : thumbViewModelT<thumbViewModel, implementation::thumbViewModel>
    {
    };
}
