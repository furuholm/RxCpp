// Copyright (c) Microsoft Open Technologies, Inc. All rights reserved. See License.txt in the project root for license information.

#pragma once
#include "rx-includes.hpp"
#include "rx-scheduler.hpp"
#include "operators/Select.hpp"

#if !defined(CPPRX_RX_OBSERVABLE_HPP)
#define CPPRX_RX_OBSERVABLE_HPP

namespace rxcpp
{
    template <class T>
    struct Observable
    {
    public:
        Observable()
        : onSubscribeFunc(nullptr)
        {
        }

        explicit Observable(OnSubscribeFunc<T> onSubscribeFunc)
        : onSubscribeFunc(onSubscribeFunc)
        {
        }

        Disposable Subscribe(std::shared_ptr<Observer<T>> observer)
        {
            return onSubscribeFunc(std::move(observer));
        }

        Disposable subscribe(
            std::function<void(const T&)> onNext,
            std::function<void()> onCompleted = nullptr,
            std::function<void(const std::exception_ptr&)> onError = nullptr
            )
        {
            auto observer = CreateObserver<T>(
                std::move(onNext), std::move(onCompleted), std::move(onError));

            return Subscribe(observer);
        }

        template<class S>
        auto select(S selector)
        -> Observable<typename std::result_of<S(const T&)>::type>
        {
            return Select<T>(onSubscribeFunc, std::move(selector));
        }

        virtual ~Observable() {}       

    private:
        OnSubscribeFunc<T> onSubscribeFunc;
    };
}

#endif
