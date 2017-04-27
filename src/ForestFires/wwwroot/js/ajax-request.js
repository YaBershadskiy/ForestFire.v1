$(document).ready(function () {
    my_ajax_req.init();
    my_ajax_req_second.init();
})


var my_ajax_req = { // создаем экземпляр объекта

    // задаем свойства объекта
    updInterval: 1000, // 10 сек. - интервал времени между запросами
    url: '/Home/AjaxWeatherResponse', // скрипт который должен отвечать на Ajax запросы
    init: function () {
        var self = my_ajax_req;
        setInterval($.proxy(my_ajax_req.requestData, self), self.updInterval);
    },

    requestData: function () {
        var self = my_ajax_req;

        // ajax запрос посредством JQuery
        $.ajax({
            url: self.url,
            type: 'POST',
            dataType: 'json',
            success: function (data) { self.update(data) },
            error: function (data) { self.error(data) },
        });
    },

    // метод принимает ответ на Ajax запрос
    update: function (Data) {
        var self = my_ajax_req;
        var weather_json = JSON.parse(Data);
        $("#weather-date").text(weather_json[0]);
        $("#weather-temp,  #degrees").text(weather_json[1]);
        $("#weather-humidity").text(weather_json[2]);
        $("#weather-wind").text(weather_json[3]);
        console.log(weather_json);
        // тут можно дописать логику после получения данных
    },

    // метод для обработки ошибок
    error: function (Data) {
        var self = my_ajax_req;
        console.log('Failed to get data');
    },
}

var my_ajax_req_second = { // создаем экземпляр объекта

    // задаем свойства объекта
    updInterval: 1000, // 10 сек. - интервал времени между запросами
    url: '/Home/AjaxSensorsResponse', // скрипт который должен отвечать на Ajax запросы
    init: function () {
        var self = my_ajax_req_second;
        setInterval($.proxy(my_ajax_req_second.requestData, self), self.updInterval);
    },

    requestData: function () {
        var self = my_ajax_req_second;

        // ajax запрос посредством JQuery
        $.ajax({
            url: self.url,
            type: 'POST',
            dataType: 'json',
            success: function (data) { self.update(data) },
            error: function (data) { self.error(data) },
        });
    },

    // метод принимает ответ на Ajax запрос
    update: function (Data) {
        var self = my_ajax_req_second;  
        console.log(Data);
        $("#humidity-id-0, #sensor-humidity").text(Data.humidity + " %");
        $("#temp-id-0, #sensor-temp").text(Data.temperature + " C");
        $("#smoke-id-0,#sensor-smoke").text(Data.smoke + " ppm");
        $("#sensor-id-0").text(Data.id);
        $("#status-id-0").text(Data.currentStatus);
        $("#date-id-0").text(Data.updated.substr(0, 10));
        // тут можно дописать логику после получения данных
    },

    // метод для обработки ошибок
    error: function (Data) {
        var self = my_ajax_req_second;
        console.log('Failed to get data');
    },
}