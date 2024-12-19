$(document).ready(function() {
    $('#postHolder').show();
    $('#postJSErrorHolder').hide();

    new ClipboardJS('.btn-code-copy');

    $('.expand-codesnippet').click(function(e){
        e.preventDefault();
        var snippetId = $(this).data('csid');
        var preTag = $('#' + snippetId).find("pre").addClass("tcs-"+snippetId);
        SyntaxHighlighter.highlight("tcs-"+snippetId);
        $('#' + snippetId).toggle();
        $('#code-copy-button-' + snippetId).toggle();

    });

    $("#markReadButton").click(function(e){
        e.preventDefault();

        $(this).html("Please wait...");
        $(this).addClass("disabled");

        window.location.href = $(this).attr("href");
    });

    $("#postFormHandle").submit(function(e) {
        $('#postFormSubmit').hide();
        $('#postLoader').show();
        $('#postError').hide();
        var postData = $(this).serializeArray();
        var formURL = $(this).attr("action");
        $.ajax(
            {
                url : formURL,
                type: "POST",
                data : postData,
                success:function(data, textStatus, jqXHR)
                {
                    console.log("Success");
                    if(data.error!=null){
                        console.log("Error");
                        $('#postError').text(data.error);
                        $('#postError').show();
                        $('#postFormSubmit').show();
                        $('#postLoader').hide();
                    } else{
                        console.log("No Errors");
                        if(data.success=="approval"){
                            $('#postInfo').text("Your message has been posted successfully, however your post must first be approved by a moderator before it is visible.");
                            $('#postInfo').show();
                            $('#postHolder').hide();
                        }else{
                            if(data.redirect!=""){
                                console.log("Redirect to "+data.redirect);
                                $('#msgBody').val("");
                                window.location = data.redirect;
                                console.log(window.location.pathname);
                                console.log(data.redirect.indexOf(window.location.pathname));
                                if(data.redirect.indexOf(window.location.pathname) == 0){
                                    location.reload();
                                }
                            }else {
                                console.log("Reload page");
                                location.reload();
                            }
                        }
                    }
                },
                error: function(jqXHR, textStatus, errorThrown)
                {
                    console.log(textStatus);
                    console.log(errorThrown);
                    $('#postError').text("An unknown error occurred!");
                    $('#postError').show();
                    $('#postFormSubmit').show();
                    $('#postLoader').hide();
                }
            });
        e.preventDefault();
    });

    //FILE UPLOAD
    var files;

    $('input[type=file]').on('change', prepareUpload);

    function prepareUpload(event)
    {
        files = event.target.files;
    }

    $('#uploadFiles').on('click', uploadFiles);

    function uploadFiles(event)
    {
        console.log("upload started");

        $('#uploadError').hide();

        event.stopPropagation();
        event.preventDefault();

        var uploadFileValue = $("#fileUploadBox").val();

        if(uploadFileValue!=""){
            $('.postFormAttachments').hide();
            $('#uploadLoader').show();

            var data = new FormData();
            $.each(files, function(key, value)
            {
                data.append(key, value);
            });

            if($('#auid').val()) {
                data.append('auid', $('#auid').val());
            }else if($('#mid').val()){
                data.append('mid', $('#mid').val());
            }else {
                $('#uploadError').html("AUID or MID missing");
                $('#uploadError').show();
                $('.postFormAttachments').show();
                $('#uploadLoader').hide();
            }

            $.ajax({
                url: '/upload/file',
                type: 'POST',
                data: data,
                cache: false,
                dataType: 'json',
                processData: false,
                contentType: false,
                success: function(data, textStatus, jqXHR)
                {
                    if(typeof data.error === 'undefined')
                    {
                        var attachmentString = "";

                        $.each(data.files, function(index, value){
                            attachmentString += $("#filesAttached").html() + "<div style='float:left;padding: 5px;border: 2px solid #7d7d7d;margin: 0 5px 0 0;max-width: 200px;text-align: center;background: #929292;color: #ffff;'><div style='margin: 0 0 5px 0;'>" + value.name + "</div>";

                            if (value.name.substr(-3,3) == 'gif' ||
                                value.name.substr(-3,3) == 'jpg' ||
                                value.name.substr(-4,4) == 'jpeg' ||
                                value.name.substr(-3,3) == 'png'
                            ) {
                                attachmentString += "<button type='button' class='btn btn-sm btn-default' onclick=\"injectText('[img]https://forum.thegamecreators.com/attachment/" + value.id + "[/img]');\"><i class='fa fa-picture-o' aria-hidden='true'></i> Embed</button>";
                            }

                            attachmentString += "</div>";

                            $("#filesAttached").html(attachmentString);
                        });

                        $('#fileUploadBox').replaceWith($('#fileUploadBox').val('').clone(true));
                        $('.postFormAttachments').show();
                        $('#uploadLoader').hide();
                    }
                    else
                    {
                        $('#uploadError').html(data.error);
                        $('#uploadError').show();
                        $('.postFormAttachments').show();
                        $('#uploadLoader').hide();
                    }
                },
                error: function(jqXHR, textStatus, errorThrown)
                {
                    $('#uploadError').html(textStatus);
                    $('#uploadError').show();
                    $('.postFormAttachments').show();
                    $('#uploadLoader').hide();
                }
            });
        } else {
            $('#uploadError').show();
            $('#uploadError').html("No file was selected");
            $('#uploadLoader').hide();
        }
    }

});