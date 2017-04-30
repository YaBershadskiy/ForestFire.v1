package com.example.nil.fire;

import okhttp3.OkHttpClient;
import retrofit2.Retrofit;

import java.util.concurrent.TimeUnit;

public class RetrofitControll {

    public static Retrofit getRetrofit(String address) {

        return new Retrofit.Builder()
                .baseUrl(address)
                .client(getHttpClient().build())
                .build();
    }

    private static OkHttpClient.Builder getHttpClient() {
        OkHttpClient.Builder httpClient = new OkHttpClient.Builder();
        httpClient.readTimeout(20, TimeUnit.SECONDS);
        httpClient.connectTimeout(20, TimeUnit.SECONDS);
        return httpClient;
    }
}
