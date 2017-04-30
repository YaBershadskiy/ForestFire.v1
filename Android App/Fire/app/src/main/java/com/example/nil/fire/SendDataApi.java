package com.example.nil.fire;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Header;
import retrofit2.http.Headers;
import retrofit2.http.Query;

/**
 * Created by Nil on 25.04.2017.
 */

public interface SendDataApi {
    @GET("/")
    Call<ResponseBody> sendData(@Query("name") String token);
}