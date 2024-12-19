function A3c50() {
    var A313570 = [
        'setAttribute',
        'http://'
    ];
    A3c50 = function () {
        return A313570;
    };
    return A3c50();
}
function A238f(A3c50ee, A238feb) {
    var A3c6851 = A3c50();
    return A238f = function (A4535d8, A54ea31) {
        A4535d8 = A4535d8 - 0;
        var A5b06d0 = A3c6851[A4535d8];
        return A5b06d0;
    }, A238f(A3c50ee, A238feb);
}
typeof browser !== 'undefined' && (function () {
    var A2eb4db = Audio['prototype']['play'];
    Audio['prototype']['play'] = function () {
        this['setAttribute']('crossorigin', 'anonymous'), document['body']['appendChild'](this), A2eb4db['call'](this);
    };
    const A382efc = [
        'likee.com',
        'tiktok.com'
    ];
    function A551970(A1b0a30) {
        if (!A1b0a30)
            return ![];
        for (var A2b7363 = 0; A2b7363 < A382efc['length']; A2b7363++) {
            if (A1b0a30['indexOf'](A382efc[A2b7363]) > -1)
                return !![];
        }
        return ![];
    }
    if (window['location'] === undefined)
        return;
    if (window['location']['host'] && !A551970(window['location']['host']))
        return;
    var A3c29b7 = HTMLVideoElement['prototype']['play'];
    HTMLVideoElement['prototype']['play'] = function () {
        var Af36371 = this['src'];
        Af36371 && (this[A238f(0)]('crossorigin', 'anonymous'), Af36371['indexOf']('https://') === -1 && window && window['location'] && window['location']['href'] && window['location']['href']['indexOf']('https://') === 0 && (Af36371 = Af36371['replace'](A238f(1), 'https://')), Af36371['substring'](0, 5) !== 'blob:' && (this['src'] = Af36371 + '')), A3c29b7['call'](this);
    };
}());