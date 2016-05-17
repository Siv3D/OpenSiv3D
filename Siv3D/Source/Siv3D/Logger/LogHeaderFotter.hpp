//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/String.hpp>

const static s3d::String headerA =
LR"(<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8" />
<title>)";

const static s3d::String headerB =
LR"( Log</title>
<style>
body		{ background-color: #f9f9f9; font-family: 'Segoe UI','メイリオ','Meiryo','ヒラギノ角ゴ Pro W3','Hiragino Kaku Gothic Pro','Osaka','ＭＳ Ｐゴシック','MS PGothic','Arial',sans-serif; }
h2			{ color: #333333; text-align: center; font-size: 28px; }
h3			{ color: #555555; text-align: center; font-size: 24px; }
div			{ font-size: 14px; line-height: 2; }
div.error	{ padding-left: 14px; background: #f44336; color: #ffffff; }
div.fail	{ padding-left: 14px; background: #ff9800; color: #ffffff; }
div.warning	{ padding-left: 14px; background: #ff9800; color: #ffffff; }
div.script	{ padding-left: 14px; background: #d9eeda; color: #333333; }
div.app		{ padding-left: 14px; background: #ffffff; color: #333333; }
div.info	{ padding-left: 14px; background: #e3f2fd; color: #333333; }
div.debug	{ padding-left: 14px; background: #f5f5f5; color: #333333; }
div.c0		{ color: #333333; text-align: center; font-size: 20px; }
div.c1		{ padding-bottom: 8px; color: #555555; text-align: center; font-size: 12px; }
div.c2		{ padding-bottom: 24px; color: #888888; text-align: center; font-size: 9px; }
div.messages { margin: 0 12% 28px; padding 0 0 28px; border: 1px solid; border-color: #cccccc; border-radius: 2px; box-shadow: 0 1px 1px rgba(0,0,0,.05); }
</style>
</head>
<body>
<h2>)";

const static s3d::String headerC =
LR"( Log</h2>
<div class="messages">
)";

const static s3d::String logLevel[]{
	LR"(<div class="error">)",
	LR"(<div class="fail">)",
	LR"(<div class="warning">)",
	LR"(<div class="script">)",
	LR"(<div class="app">)",
	LR"(<div class="info">)",
	LR"(<div class="debug">)",
};

const static s3d::String pEnd = L"</div>\n";

const static s3d::String footer =
LR"-(</div>
<h3>Licenses</h3>
<div class="c0">Siv3D Engine</div>
<div class="c1">Copyright (c) 2008-2016 Ryo Suzuki<br>Copyright (c) 2016 OpenSiv3D Project</div>
<div class="c2">
Permission is hereby granted, free of charge, to any person obtaining a copy<br>
of this software and associated documentation files (the “Software”), to deal<br>
in the Software without restriction, including without limitation the rights<br>
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell<br>
copies of the Software, and to permit persons to whom the Software is<br>
furnished to do so, subject to the following conditions:<br>
<br>
The above copyright notice and this permission notice shall be included in all<br>
copies or substantial portions of the Software.<br>
<br>
THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR<br>
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,<br>
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE<br>
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER<br>
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,<br>
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE<br>
SOFTWARE.<br>
</div>
<div class="c0">Formatting library for C++</div>
<div class="c1">Copyright (c) 2012 - 2015, Victor Zverovich</div>
<div class="c2">
 Redistribution and use in source and binary forms, with or without<br>
 modification, are permitted provided that the following conditions are met:<br>
<br>
 1. Redistributions of source code must retain the above copyright notice, this<br>
    list of conditions and the following disclaimer.<br>
 2. Redistributions in binary form must reproduce the above copyright notice,<br>
    this list of conditions and the following disclaimer in the documentation<br>
    and/or other materials provided with the distribution.<br>
<br>
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND<br>
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED<br>
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE<br>
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR<br>
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES<br>
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;<br>
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND<br>
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT<br>
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS<br>
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.<br>
</div>
<div class="c0">Flexible and Economical UTF-8 Decoder</div>
<div class="c1">Copyright (c) 2008-2009 Bjoern Hoehrmann &lt;bjoern@hoehrmann.de&gt;</div>
<div class="c2">
Permission is hereby granted, free of charge, to any person obtaining a copy<br>
of this software and associated documentation files (the "Software"), to deal<br>
in the Software without restriction, including without limitation the rights<br>
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell<br>
copies of the Software, and to permit persons to whom the Software is<br>
furnished to do so, subject to the following conditions:<br>
<br>
The above copyright notice and this permission notice shall be included in all<br>
 copies or substantial portions of the Software.<br>
<br>
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR<br>
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,<br>
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE<br>
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER<br>
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,<br>
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE<br>
SOFTWARE.<br>
</div>
<div class="c0">double-conversion</div>
<div class="c1">Copyright 2006-2011, the V8 project authors. All rights reserved.</div>
<div class="c2">
Redistribution and use in source and binary forms, with or without<br>
modification, are permitted provided that the following conditions are<br>
met:<br>
<br>
    * Redistributions of source code must retain the above copyright<br>
      notice, this list of conditions and the following disclaimer.<br>
    * Redistributions in binary form must reproduce the above<br>
      copyright notice, this list of conditions and the following<br>
      disclaimer in the documentation and/or other materials provided<br>
      with the distribution.<br>
    * Neither the name of Google Inc. nor the names of its<br>
      contributors may be used to endorse or promote products derived<br>
      from this software without specific prior written permission.<br>
<br>
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS<br>
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT<br>
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR<br>
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT<br>
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,<br>
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT<br>
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,<br>
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY<br>
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT<br>
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE<br>
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.<br>
</div>
<div class="c0">Convenient Constructs For Stepping Through a Range of Values</div>
<div class="c1">Copyright (c) Mikhail Semenov</div>
<div class="c2">Licenced with the Code Project Open Licence (CPOL) http://www.codeproject.com/info/cpol10.aspx </div>
<br>
</body>
</html>)-";
