﻿<?xml version='1.0' encoding='UTF-8'?>
<LVClass LVVersion="9008000">
	<Property Name="NI.Lib.ContainingLib" Type="Str">POLARIS BME DG.lvlib</Property>
	<Property Name="NI.Lib.ContainingLibPath" Type="Str">../../../POLARIS BME DG.lvlib</Property>
	<Property Name="NI.Lib.Description" Type="Str">The class inherits from BME_DG_G05.

overwrites initilize.vi

author: Alexander Kessler, Helmholtz-Institut-Jena 
maintainer: Alexander Kessler: alexander.kessler@uni-jena.de

Last Change:
License Agreement for this software:

Copyright (C)
Helmholtz-Institut-Jena
Fröbelsteg 3
07743 Jena
Germany

Contact: alexander.kessler@uni-jena.de

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the license, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General License for more details (http://www.gnu.org).</Property>
	<Property Name="NI.Lib.HelpPath" Type="Str"></Property>
	<Property Name="NI.Lib.Icon" Type="Bin">#1#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!)?!!!*Q(C=\&gt;4"4=.!%)8B"_,!.2WAN0";3!NJ96L)F7.;G"&lt;31M\=JI7UE"&lt;-\W5322%C3)$AQ*I.]&lt;.X^MN[:7GU2_F"U[XW]G(\T07X)K&gt;3@&gt;:@2J``TH8[L*/,[Z@DX][PRE_H];&gt;[U\PTHW?:LPXP`.SP``Y&lt;4@`NP`VO?\[Z38^]T^ZJ@B(2CZ\UI&amp;PT6&amp;/2&amp;XG2&amp;XG2&amp;XG3*XG3*XG3*XG1"XG1"XG1"\H*47ZSEZP=Z/-A&amp;\H)21[JG,S9K#B;&amp;#BOBK,CI`!5HM*4?$B6Y3E]B;@Q&amp;"ZO5?%J0)7H]"1?BKHQ&amp;*\#5XA+$[7'J-:"DK@Q5&amp;[**`%EHM34?*B3C3="**-FB:-C-*2=4,YEHM34?0CKR*.Y%E`C34R=6O**0)EH]31?BIR6S;':$X)]F&amp;(A#4S"*`!%(EIL]!3?Q".Y!A`4+@!%HA!24"A5B["A5("$="*Y!A``&amp;(A#4_!*0)'(3_-*R6C:74-@Z(C-RXC-RXC-BR)S(O-R(O-R(ML+?)T(?)T(?*B+RG-]RG-A:F+GFSFG"JK&lt;4'!]`)X&gt;YP'5=EA]$KEXLXJ4KD?&lt;?B/J.Y@[I;M@JPIBK2&gt;@P;DKR6)PAPL(K&gt;&amp;KD(I3^?$Z2BXZ0.$X^"V^3^`1V`16@5F@T%/`_=&lt;D];D$Y;$^@K`&gt;&lt;K@N&gt;KP.:K0V?KX6;K8F=KH&amp;9H&amp;_$4RRH&amp;])@_'^^#=-^\KMSRK^!GA[0)%!!!!!</Property>
	<Property Name="NI.Lib.Version" Type="Str">1.0.0.0</Property>
	<Property Name="NI.LVClass.ClassNameVisibleInProbe" Type="Bool">true</Property>
	<Property Name="NI.LVClass.DataValRefToSelfLimitedLibFlag" Type="Bool">true</Property>
	<Property Name="NI.LVClass.FlattenedPrivateDataCTL" Type="Bin">#1#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!",Z5F.31QU+!!.-6E.$4%*76Q!!$T!!!!0*!!!!)!!!$R!!!!!O!!!!!B214UR"5EF4)%*.23"%2SZM&gt;GRJ9B2#456@2%&gt;@2T!V5$)O&lt;(:D&lt;'&amp;T=Q!!!!!!?!E!A!!!-!!!+!!!!!!!!!1!!Q!]!,Q!(U#!!A!!!!!"!!%!"P````]!!!!!!!!!!!!!!!#&gt;.!-NL(B73;]EWUHE_8W[!!!!$!!!!"!!!!!!+_:GM:A-0E;AX+U#P=/&gt;VN1&gt;D.G0!,)%[9!*G/TY1HY!!%!!!!!!!!!!!"!!!!!!!!!!!!!!!!!!!!!!!!!!:Q!"4&amp;:$1TJ14UR"5EF4)%*.23"%2SZM&gt;GRJ9DJ#456@2%&gt;@2T!V5$)O&lt;(:D&lt;'&amp;T=TJ#456@2%&gt;@2T!V5$)O9X2M!!!!!!!!!1!#6EF-1A!!!!!!!&amp;"53$!!!!!&amp;!!%!!1!!!!!#!!-!!!!!!A!"!!!!!!!1!!9!!B!!%!%1!"!%-!!1!!!!!$Q!!!%1?*RD9-!%`Y%!3$%S-$#$O#TIYP_B!)N7CA'SO&gt;DM)-Z?2K!;JC]-5!^!!$-K&amp;QD9M/A%!.LH(@-!!!"+!!&amp;73524/F"04%&amp;336-A1EV&amp;)%2(,GRW&lt;'FC/E*.26^%2V^(-$61-CZM&gt;G.M98.T/E*.26^%2V^(-$61-CZD&gt;'Q!!!!!!!!!!!-!!!!!!(A!!!#U?*RT:'"AS$3W-+NA1)$E`*25%,U!C&amp;]TR-&gt;&amp;25&lt;((JY1WJWDQB%='"17PI-2+)%JX&amp;X+M%-,+.0JJL&amp;$#5Q\\(!%US[B,U$G^;;IM-#U:1$Z"Y(GA)T[$Q1A?59':A:`BH#'?#3X/0O\O#*RQ7Y#!$2"*VE!!!!,#1#!)A!!!TEO-!!!!!!!A0````_!!!!"A!!!!9!!!!'!!!!"A!!!!9!!!!'!!!!"A!!!!9!!!!'!!!!"A!!!!9"A!!'"G!!"BA9!!:A"A!'A!%!"M!$!!;Q$1!'D$M!"I06!!;!KQ!'A.5!"I#L!!;!V1!'A+M!"I$6!!:ALA!''.A!"A&lt;A!!9"A!!(`````!!!%!0```````````````````````````````````````````Q!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!0``!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!``]!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!$``Q!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!0``!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!``]!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!$``Q!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!0``!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!``]!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!$``Q!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!0``!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!``]!!!!!!!!!!,GZ!!!!!!!!!!!!!!!!!!!!!!!!!!$``Q!!!!!!!,H2R=P2O1!!!!!!!!!!!!!!!!!!!!!!!0``!!!!!,H2R&lt;_`P\`,U&lt;E!!!!!!!!!!!!!!!!!!!!!``]!!,H2R&lt;_`P\_`P\_`S^'Z!!!!!!!!!!!!!!!!!!$``Q$,R&lt;_`P\_`P\_`P\_`P]P2!!!!!!!!!!!!!!!!!0``!-8&amp;P\_`P\_`P\_`P\_``]M!!!!!!!!!!!!!!!!!``]!R=P,R&lt;_`P\_`P\_`````R1!!!!!!!!!!!!!!!!$``Q$&amp;S]P,S]7`P\_````````&amp;!!!!!!!!!!!!!!!!!0``!-8,S]P,S]P&amp;U@```````]5!!!!!!!!!!!!!!!!!``]!R=P,S]P,S]P`````````R1!!!!!!!!!!!!!!!!$``Q$&amp;S]P,S]P,S``````````&amp;!!!!!!!!!!!!!!!!!0``!-8,S]P,S]P,`````````]5!!!!!!!!!!!!!!!!!``]!R=P,S]P,S]P`````````R1!!!!!!!!!!!!!!!!$``Q$&amp;S]P,S]P,S``````````&amp;!!!!!!!!!!!!!!!!!0``!-P,S]P,S]P,````````S]M!!!!!!!!!!!!!!!!!``]!!-8&amp;S]P,S]P`````S^(&amp;!!!!!!!!!!!!!!!!!!$``Q!!!!$&amp;S]P,S```S]P&amp;!!!!!!!!!!!!!!!!!!!!!0``!!!!!!!!R=P,S]O`!!!!!!!!!!!!!!!!!!!!!!!!``]!!!!!!!!!!-7`!!!!!!!!!!!!!!!!!!!!!!!!!!$```````````````````````````````````````````]!!!!#!!%!!!!!!%I!!5:13&amp;![5%^-16**5S"#455A2%=O&lt;(:M;7)[1EV&amp;8U2(8U=Q.6!S,GRW9WRB=X-[1EV&amp;8U2(8U=Q.6!S,G.U&lt;!!!!!!!!!!!!Q!!!!!#&gt;!!!"."YH+W5TWM4124(X[R&lt;G12,*GGV$&lt;9GVEF33A)CN4^#K]6/B5IJGNAC8D4NRB^1D#3J?'IP?UGB*S%(I?!J6Q]Z^#K3WXLI14T91_B`Y+5IW-X[:N.EYV&lt;;CTEMSW9_\]W]\Y="5,_Q@K5"'S91&gt;IAP#S:Y.9-!V")5DH^MC@Q'UBME*MT1*&lt;;P.-C!#2=U)UKPCR,]Q+87"SM'8]EK/]#FZVE1+XF.]'F'H`]?LT0_=9#8OFIF@8#:&lt;:/']IC(@N*N09@&gt;1"_74X_#.)#)K[KK$^X0P-LK8(\V*'D1,OERA1GD/]`L-;S)L4`&lt;*:5YY=J5KS2AS7'I6KM/Z'^#58M&lt;%]A1$E"'F@AJ4%!9AQ6?D^O-VW;QTWCLDQAVXMG^3]C.^AC$)9L=W_-D3\&lt;&amp;G40`Z&amp;[9U-PL&gt;WC1(GD@O\I@[,N!A.3?5'P87J?]@V'G9+].9"#2*'&amp;J@%_&lt;-+)&lt;SF.17_/&gt;BCU\"L56QR4'1/\;-8B%C9'4Q^9:/1CV.D1YO\:?+'&lt;TY&gt;ST]/J;JF!)P][`@*-J:M.;JJAZG&gt;#U-$TD]P3SG3U(^)!+E\$=/?U=6#I6(!!_(@17IHW]XO:]^GE?NS?O/:/48:X*X=&lt;*C6]0H]PJ2:++,3QYKNZ!6@X-P:O`6,XZ`V5&gt;1Y-W8+J##K+Q=IJWYUX)5288!YR"[B2G!JH.4F7233'T=L;KES&gt;5F;R,V8+Z\&amp;9VW6:6*;3JKLZH(6F(+#S/6Y527,;&amp;"=^CR]\J0EV(9O?YM'D1^1?&lt;Q]K&lt;*FQ5MY&amp;0&lt;&amp;[[4O@J(.P"#0(CO52X['(N7`OCK3WULS&gt;^4\F'LP$X)&gt;L`"_,B79)!!!!%!!!!)!!!!!!!!!!!!!!!!!!!!%I!!5*%3&amp;![5%^-16**5S"#455A2%=O&lt;(:M;7)[1EV&amp;8U2(8U=Q.6!S,GRW9WRB=X-[1EV&amp;8U2(8U=Q.6!S,G.U&lt;!!!!!!!!!!!!Q!!!!!!9A!!!(*YH'.A9-A4E'$[RV$XFY&amp;*Y#O1)@W8A6H1D`%X!Q/HH]"B)-UI)!E5FPX,Q#[I$2&lt;70K,,Q1!&amp;KGS-(*)=BQ5ZQ$)=,2I-````Z`B[Z"J=R2%@/&amp;.FFDS("!!59BE!!!!!!!!%!!!!"Q!!!:1!!!!'!!!!)6^O;6^-98.U3WZP&gt;WZ0&gt;WZJ&lt;G&gt;-6E.M98.T1WRV=X2F=AE!A!!!!!!"!!A!-0````]!!1!!!!!!$A!!!!%!"A"1!!!!!1!!!!!!!!!!!"J-6E.M98.T5(*J&gt;G&amp;U:52B&gt;'&amp;597*0=G2F=AE!A!!!!!!#!!5!"Q!!$!"!!!(`````!!!!!1!"!!!!!!!!!!!!!!!&lt;4&amp;:$&lt;'&amp;T=V"S;8:B&gt;'6%982B6'FN:8.U97VQ#1#!!!!!!!%!"1!(!!!"!!$,GALO!!!!!!!!!#:-6E.M98.T5(*J&gt;G&amp;U:52B&gt;'&amp;-98.U18"Q&lt;'FF:&amp;2J&lt;76T&gt;'&amp;N=!E!A!!!!!!"!!5!"Q!!!1!!SZI+\A!!!!!!!!!;4&amp;:$&lt;'&amp;T=V"S;8:B&gt;'6%982B6(FQ:52F=W-*!)!!!!!!!1!)!$$`````!!%!!!!!!!Y!!!!"!!9!5!!!!!%!!!!!!!!!!!!?4&amp;:$&lt;'&amp;T=V"S;8:B&gt;'6%982B2':M&gt;%2B&gt;'&amp;4;8JF#1#!!!!!!!%!"1!$!!!"!!!!!!!!!!!!!!!!!!1!!A!)!!!!"!!!!%!!!!!I!!!!!A!!"!!!!!!&amp;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!E!!!!.[?*S.EEVPUU!1BN`AOGG3@K2N3K&amp;@'#B1PEJ"YGY;ESA3&lt;;)EQ,'YO_P+9O-VXH76=/*X]*@Y,UD=/4!&lt;.SL=O-W]]_\OMT-$Y#5_Y^?0\^7@!*R'L`PO4&lt;]T])Z0XHJ"_V"?SPC]1=F:U$ZL(\XOP3+*S6$L_D]C-R)(@A`9&lt;=J='Z&amp;Z+P+G0C`.YMP1#)_(*E16$#D^2AEO(&amp;$+91FO9!'@+&amp;IEJ5?:A\H#CA/S6PQSH%B?9-(`ZKC_+13B)N4J31&gt;F/FVR=BZB`X]1L-@B%&lt;_+T(A7+4G,R.BAD5DGC;*'6%N9RAJ7@/,E4(53,M:!T:_('[&gt;.F7$6&gt;V(4EY1&amp;M5ZF/#'LCQL&gt;EI8PN?"E&gt;4%8S&gt;!!3XY*]UQFJ`H)*E20_E5Q[&amp;YHQZ-/H;!?=$XY#KT4Y58/V==M.K+JO!#W37K1&gt;#I%?@,T$ZW"#4/4JSB19EW--1O.SK9I#\%?M&amp;#'G&lt;X.Q;*+!WJ&amp;.YKU-0;)AZLZ3^EE967-"&lt;.;TW28]B213".9L#7[NMR5/OG,,^0`O6,2%T1&lt;GGQE6+%F14T3":0V^D,&amp;/HS-$2+7L&gt;$+V+BP%KN.8&gt;62L*FM52-U#-.&amp;05^S[G!LFF*ERR-D#NSKTM_(EV49PG(,N\MT6W=U&gt;D6KUL7TH_U5F&lt;8LSF$.;HN&amp;L8&amp;&gt;MT#TKE`4X]5K&lt;=%['ND!47TC&amp;GZD#^P9I=I?\M$$8&gt;T$@?TD!2\C%?XK9TT"5TT$][P.,O'1.BGI4'/8^KG/&amp;TCCH;L^!2'(RLI!!!"@!!%!!A!$!!1!!!")!!U%!!!!!!U!U!#Z!!!!4Q!."!!!!!!.!.!!O1!!!&amp;9!$11!!!!!$1$1!,E!!!"&gt;A!#%!)!!!!U!U!#Z"F2B;'^N91:597BP&lt;7%'6'&amp;I&lt;WVB!4!!5F.31QU+!!.-6E.$4%*76Q!!$T!!!!0*!!!!)!!!$R!!!!!!!!!!!!!!!#!!!!!U!!!$O!!!!"N-35*/!!!!!!!!!62-6F.3!!!!!!!!!7B36&amp;.(!!!!!!!!!8R-38:J!!!!!!!!!:"$4UZ1!!!!!!!!!;2544AQ!!!!!!!!!&lt;B%2E24!!!!!!!!!=R-372T!!!!!!!!!?"735.%!!!!!!!!!@2W:8*T!!!!!!!!!AB*1U^/!!!!!!!!!BRJ9WQY!!!!!!!!!D"$5%-S!!!!!!!!!E2-37:Q!!!!!!!!!FB'5%BC!!!!!!!!!GR'5&amp;.&amp;!!!!!!!!!I"*5&amp;.3!!!!!!!!!J2$4F.5!!!!!!!!!KB-5%F/!!!!!!!!!LR-37*E!!!!!!!!!N"#2%BC!!!!!!!!!O2#2&amp;.&amp;!!!!!!!!!PB73624!!!!!!!!!QR%6%B1!!!!!!!!!S".65F%!!!!!!!!!T2)36.5!!!!!!!!!UB71V21!!!!!!!!!VR'6%&amp;#!!!!!!!!!X!!!!!!`````Q!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!$1!!!!!!!!!!0````]!!!!!!!!!M!!!!!!!!!!!`````Q!!!!!!!!$%!!!!!!!!!!$`````!!!!!!!!!4!!!!!!!!!!!0````]!!!!!!!!"/!!!!!!!!!!!`````Q!!!!!!!!&amp;-!!!!!!!!!!$`````!!!!!!!!!9Q!!!!!!!!!!0````]!!!!!!!!"X!!!!!!!!!!%`````Q!!!!!!!!*9!!!!!!!!!!$`````!!!!!!!!!GA!!!!!!!!!!0````]!!!!!!!!#\!!!!!!!!!!!`````Q!!!!!!!!&lt;Q!!!!!!!!!!$`````!!!!!!!!"PA!!!!!!!!!!0````]!!!!!!!!(3!!!!!!!!!!!`````Q!!!!!!!!H!!!!!!!!!!!$`````!!!!!!!!#=A!!!!!!!!!!0````]!!!!!!!!*T!!!!!!!!!!!`````Q!!!!!!!!H1!!!!!!!!!!$`````!!!!!!!!#&gt;1!!!!!!!!!!0````]!!!!!!!!+*!!!!!!!!!!!`````Q!!!!!!!!K-!!!!!!!!!!$`````!!!!!!!!#J1!!!!!!!!!!0````]!!!!!!!!-,!!!!!!!!!!!`````Q!!!!!!!!QU!!!!!!!!!!$`````!!!!!!!!$$Q!!!!!!!!!!0````]!!!!!!!!-;!!!!!!!!!#!`````Q!!!!!!!![M!!!!!""#456@2%&gt;@2T!V5$)O9X2M!!!!!!</Property>
	<Property Name="NI.LVClass.Geneology" Type="Xml"><String>

<Name></Name>

<Val>!!!!!B214UR"5EF4)%*.23"%2SZM&gt;GRJ9B2#456@2%&gt;@2T!V5$)O&lt;(:D&lt;'&amp;T=V"53$!!!!!!!!!!!!!!!!!!#!!"!!!!!!!!!1!!!!%!"A"1!!!!!1!!!!!!!!!!!!!"$ERB9F:*26=A4W*K:7.U!&amp;"53$!!!!!!!!!!!!!*!)!!!!!!!!!!!@``!!!!!1!!!!!!!1%!!!!"!!9!5!!!!!%!!!!!!!(````_!!!!!!%41EV&amp;8U2(8U*B=W5O&lt;(:D&lt;'&amp;T=V"53$!!!!!!!!!!!!!*!)!!!!!!!!!!!1!!!!!!!1!!!!!!!A%!!!!#!".!"Q!.6(*J:W&gt;F=EVP:(6M&lt;Q"5!0(,GA)4!!!!!B*#456@2%&gt;@2T!V,GRW9WRB=X-/1EV&amp;8U2(8U=Q.3ZD&gt;'Q!+E"1!!%!!"V$&lt;(6T&gt;'6S)'^G)'.M98.T)("S;8:B&gt;'5A:'&amp;U91!"!!%!!!!"`````Q!!!!%!!!!"%U*.26^%2V^#98.F,GRW9WRB=X.16%AQ!!!!!!!!!!!!#1#!!!!!!!!!!!%!!!!!!!%!!!!!!!-"!!!!!1"3!0(,GALO!!!!!B*#456@2%&gt;@2T!V,GRW9WRB=X-/1EV&amp;8U2(8U=Q.3ZD&gt;'Q!+%"1!!!&gt;1WRV=X2F=C"P:C"D&lt;'&amp;T=S"Q=GFW982F)'2B&gt;'%!!1!!!!!!!!!!!!!"%U*.26^%2V^#98.F,GRW9WRB=X.16%AQ!!!!!!!!!!!!#1#!!!!!!!!!!!%!!!!!!!%!!!!!!!!#!!!!!1"3!0(,GALO!!!!!B*#456@2%&gt;@2T!V,GRW9WRB=X-/1EV&amp;8U2(8U=Q.3ZD&gt;'Q!+%"1!!!&gt;1WRV=X2F=C"P:C"D&lt;'&amp;T=S"Q=GFW982F)'2B&gt;'%!!1!!!!!!!@````Y!!!!!!2.#456@2%&gt;@1G&amp;T:3ZM&gt;G.M98.T5&amp;2)-!!!!!!!!!!!!!E!A!!!!!!!!!!"!!!!!!!"!!!!!!!"!A!!!!%!5A$RSZI+\A!!!!)31EV&amp;8U2(8U=Q.3ZM&gt;G.M98.T$E*.26^%2V^(-$5O9X2M!#B!5!!!(5.M&gt;8.U:8)A&lt;W9A9WRB=X-A=(*J&gt;G&amp;U:3"E982B!!%!!!!!!!(````_!!!!!!)55%^-16**5S"#455A2%=O&lt;(:M;7)31EV&amp;8U2(8U=Q.3ZM&gt;G.M98.T5&amp;2)-!!!!!!!!!!!!!E!A!!!!!!!!1!!!!!!!!!"!!!!!!!#!A!!!!%!5A$RSZI+\A!!!!)31EV&amp;8U2(8U=Q.3ZM&gt;G.M98.T$E*.26^%2V^(-$5O9X2M!#B!5!!!(5.M&gt;8.U:8)A&lt;W9A9WRB=X-A=(*J&gt;G&amp;U:3"E982B!!%!!!!!!!(````_!!!!!!)55%^-16**5S"#455A2%=O&lt;(:M;7)31EV&amp;8U2(8U=Q.3ZM&gt;G.M98.T5&amp;2)-!!!!!!!!!!!!!E!A!!!!!!!!!!!!!!!!!!"!!!!!!!!!!!!!!%!5A$RSZI+\A!!!!)31EV&amp;8U2(8U=Q.3ZM&gt;G.M98.T$E*.26^%2V^(-$5O9X2M!#B!5!!!(5.M&gt;8.U:8)A&lt;W9A9WRB=X-A=(*J&gt;G&amp;U:3"E982B!!%!!!!!!!(````_!!!!!!)55%^-16**5S"#455A2%=O&lt;(:M;7)31EV&amp;8U2(8U=Q.3ZM&gt;G.M98.T5&amp;2)-!!!!!!!!!!!!!E!A!!!!!!!!!!!!!!#!!!!%E*.26^%2V^(-$5O&lt;(:D&lt;'&amp;T=Q!!!"2#456@2%&gt;@2T!V5$)O&lt;(:D&lt;'&amp;T=Q</Val>

</String>

</Property>
	<Property Name="NI.LVClass.IsTransferClass" Type="Bool">false</Property>
	<Property Name="NI.LVClass.ParentClassLinkInfo" Type="Bin">#1#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!"9!!!!!B214UR"5EF4)%*.23"%2SZM&gt;GRJ9B*#456@2%&gt;@2T!V,GRW9WRB=X.16%AQ!!!!*!!"!!1!!!J#456@2%&gt;@2T!V%E*.26^%2V^(-$5O&lt;(:D&lt;'&amp;T=Q!!!!!</Property>
	<Property Name="NI_IconEditor" Type="Str">48 57 48 48 56 48 50 50 13 0 0 0 0 1 23 21 76 111 97 100 32 38 32 85 110 108 111 97 100 46 108 118 99 108 97 115 115 0 0 1 0 0 0 0 0 9 0 0 26 1 1 100 1 100 80 84 72 48 0 0 0 4 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 1 15 13 76 97 121 101 114 46 108 118 99 108 97 115 115 0 0 1 0 0 0 0 0 7 0 0 12 182 0 0 0 0 0 0 0 0 0 0 12 158 0 40 0 0 12 152 0 0 12 0 0 0 0 0 0 32 0 32 0 24 0 0 0 0 0 255 255 255 0 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 0 132 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 0 0 0 127 255 255 254 127 255 255 254 127 255 255 254 127 255 255 254 127 255 255 254 127 255 255 254 127 255 255 254 127 255 255 254 127 255 255 254 127 255 255 254 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 4 70 105 108 108 100 1 0 2 0 0 0 1 15 13 76 97 121 101 114 46 108 118 99 108 97 115 115 0 0 1 0 0 0 0 0 7 0 0 12 185 0 0 0 0 0 0 0 0 0 0 12 158 0 40 0 0 12 152 0 0 12 0 0 0 0 0 0 32 0 32 0 24 0 0 0 0 0 255 255 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 7 86 73 32 73 99 111 110 100 1 0 2 0 0 0 6 68 71 95 80 48 53 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 11 83 109 97 108 108 32 70 111 110 116 115 0 1 9 1 0

</Property>
	<Item Name="BME_DG_G05P2.ctl" Type="Class Private Data" URL="BME_DG_G05P2.ctl">
		<Property Name="NI.LibItem.Scope" Type="Int">2</Property>
	</Item>
	<Item Name="Initialize.vi" Type="VI" URL="../Initialize.vi">
		<Property Name="NI.ClassItem.ConnectorPane" Type="Bin">#1#!!!!!!!)!"1!&amp;!!!-!%!!!@````]!!!!"!!%!!!%W!!!!#A!-1#%'=X2B&gt;(6T!!!,1!-!"'.P:'5!!""!-0````]'=W^V=G.F!!!71&amp;!!!Q!!!!%!!AFF=H*P=C"P&gt;81!"!!!!%2!=!!?!!!L&amp;&amp;"04%&amp;336-A1EV&amp;)%2(,GRW&lt;'FC&amp;%*.26^%2V^(-$61-CZM&gt;G.M98.T!!Z#456@2%&gt;@2T!V)'^V&gt;!!!)%"1!!-!!!!"!!)4:8*S&lt;X)A;7YA+'ZP)'6S=G^S+1!,1!-!"52()%ZS!%*!=!!?!!!L&amp;&amp;"04%&amp;336-A1EV&amp;)%2(,GRW&lt;'FC&amp;%*.26^%2V^(-$61-CZM&gt;G.M98.T!!V#456@2%&gt;@2T!V)'FO!$Q!]!!-!!-!"!!%!!5!"!!%!!1!"!!'!!1!"Q!)!Q!!?!U)!!!!!)U,!!!!!!!!!!!+!!!!#!#3!!!!!!%!#1!!!!!</Property>
		<Property Name="NI.ClassItem.ExecutionSystem" Type="Int">-1</Property>
		<Property Name="NI.ClassItem.Flags" Type="Int">0</Property>
		<Property Name="NI.ClassItem.IsStaticMethod" Type="Bool">false</Property>
		<Property Name="NI.ClassItem.MethodScope" Type="UInt">1</Property>
		<Property Name="NI.ClassItem.Priority" Type="Int">1</Property>
		<Property Name="NI.ClassItem.State" Type="Int">1350574608</Property>
	</Item>
</LVClass>
