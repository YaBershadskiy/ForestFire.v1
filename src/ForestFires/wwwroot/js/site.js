var hoverFunc = function (par, phone) {//view hover-effect on focus element
    $(par).bind('mouseenter', function () {
        $(phone).stop(true, false).fadeIn(500);
        $(par).css("cursor", "pointer");
    });

    $(par).bind('mouseleave', function () {
        $(phone).stop(true, false).fadeOut(500);
     
    });
}

$(document).ready(function () {
    var trigger = true;

    var animateTest = function () {//search func
        $('#find').unbind('click');
        if (trigger) {
            $("#input-text").animate({
                width: "300px",
                "padding-left": "10px",
            }, 1500,
             (function () {
                 $('#find').bind('click', animateTest);
             }));
            trigger = false;
            $("#input-text").val('');
        }
        else {
            $("#input-text").animate({
                width: "0px",
                "padding-left": "0px",
            }, 1500,
             (function () {
                 $('#find').bind('click', animateTest);
             }));
            trigger = true;
        }
    }

    $('#find').bind('click', animateTest);

    hoverFunc('#info-group-1', '#blue-phone-about-1');
    hoverFunc('#info-group-2', '#blue-phone-about-2');
    hoverFunc('#info-group-3', '#blue-phone-about-3');

});

