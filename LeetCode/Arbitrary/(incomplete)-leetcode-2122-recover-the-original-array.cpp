// LeetCode-2122: https://leetcode.com/problems/recover-the-original-array/
// hard problem

// 1st soln (commented out) is correct, but goes TLE on following LC input (2nd soln works for this one)
// [522364120,404489734,73377143,68154641,875141660,208102664,993519610,855903585,179628014,906740652,76405247,10803579,766597179,274088176,844119893,9186347,44266184,115009317,489538266,815295469,848059589,556956747,568168541,467762051,755385385,248570678,757625462,62165349,436509576,743007379,425297782,987877827,746413668,124766661,196890870,518666131,263323518,693749721,867115379,352131849,724284460,363343643,569964478,682537927,478973845,168416220,285299970,734292511,54520732,723080717,103797523,581176272,307562412,22015373,252111724,296350618,33054390,917952446,726464742,87617041,529877925,730318363,737676536,393277940,859271383,826507263,79366435,135978455,741530157,735496254,20398141,982307816,754219173,198109486,65732526,500750060,54339173,999089621,511152326,855331687,237358884,209321280,65550967,863929866]

// 2nd soln is correct, but goes TLE on following LC input
// [1,999999,2,1000000,5,1000003,10,1000008,17,1000015,26,1000024,37,1000035,50,1000048,65,1000063,82,1000080,101,1000099,122,1000120,145,1000143,170,1000168,197,1000195,226,1000224,257,1000255,290,1000288,325,1000323,362,1000360,401,1000399,442,1000440,485,1000483,530,1000528,577,1000575,626,1000624,677,1000675,730,1000728,785,1000783,842,1000840,901,1000899,962,1000960,1025,1001023,1090,1001088,1157,1001155,1226,1001224,1297,1001295,1370,1001368,1445,1001443,1522,1001520,1601,1001599,1682,1001680,1765,1001763,1850,1001848,1937,1001935,2026,1002024,2117,1002115,2210,1002208,2305,1002303,2402,1002400,2501,1002499,2602,1002600,2705,1002703,2810,1002808,2917,1002915,3026,1003024,3137,1003135,3250,1003248,3365,1003363,3482,1003480,3601,1003599,3722,1003720,3845,1003843,3970,1003968,4097,1004095,4226,1004224,4357,1004355,4490,1004488,4625,1004623,4762,1004760,4901,1004899,5042,1005040,5185,1005183,5330,1005328,5477,1005475,5626,1005624,5777,1005775,5930,1005928,6085,1006083,6242,1006240,6401,1006399,6562,1006560,6725,1006723,6890,1006888,7057,1007055,7226,1007224,7397,1007395,7570,1007568,7745,1007743,7922,1007920,8101,1008099,8282,1008280,8465,1008463,8650,1008648,8837,1008835,9026,1009024,9217,1009215,9410,1009408,9605,1009603,9802,1009800,10001,1009999,10202,1010200,10405,1010403,10610,1010608,10817,1010815,11026,1011024,11237,1011235,11450,1011448,11665,1011663,11882,1011880,12101,1012099,12322,1012320,12545,1012543,12770,1012768,12997,1012995,13226,1013224,13457,1013455,13690,1013688,13925,1013923,14162,1014160,14401,1014399,14642,1014640,14885,1014883,15130,1015128,15377,1015375,15626,1015624,15877,1015875,16130,1016128,16385,1016383,16642,1016640,16901,1016899,17162,1017160,17425,1017423,17690,1017688,17957,1017955,18226,1018224,18497,1018495,18770,1018768,19045,1019043,19322,1019320,19601,1019599,19882,1019880,20165,1020163,20450,1020448,20737,1020735,21026,1021024,21317,1021315,21610,1021608,21905,1021903,22202,1022200,22501,1022499,22802,1022800,23105,1023103,23410,1023408,23717,1023715,24026,1024024,24337,1024335,24650,1024648,24965,1024963,25282,1025280,25601,1025599,25922,1025920,26245,1026243,26570,1026568,26897,1026895,27226,1027224,27557,1027555,27890,1027888,28225,1028223,28562,1028560,28901,1028899,29242,1029240,29585,1029583,29930,1029928,30277,1030275,30626,1030624,30977,1030975,31330,1031328,31685,1031683,32042,1032040,32401,1032399,32762,1032760,33125,1033123,33490,1033488,33857,1033855,34226,1034224,34597,1034595,34970,1034968,35345,1035343,35722,1035720,36101,1036099,36482,1036480,36865,1036863,37250,1037248,37637,1037635,38026,1038024,38417,1038415,38810,1038808,39205,1039203,39602,1039600,40001,1039999,40402,1040400,40805,1040803,41210,1041208,41617,1041615,42026,1042024,42437,1042435,42850,1042848,43265,1043263,43682,1043680,44101,1044099,44522,1044520,44945,1044943,45370,1045368,45797,1045795,46226,1046224,46657,1046655,47090,1047088,47525,1047523,47962,1047960,48401,1048399,48842,1048840,49285,1049283,49730,1049728,50177,1050175,50626,1050624,51077,1051075,51530,1051528,51985,1051983,52442,1052440,52901,1052899,53362,1053360,53825,1053823,54290,1054288,54757,1054755,55226,1055224,55697,1055695,56170,1056168,56645,1056643,57122,1057120,57601,1057599,58082,1058080,58565,1058563,59050,1059048,59537,1059535,60026,1060024,60517,1060515,61010,1061008,61505,1061503,62002,1062000,62501,1062499,63002,1063000,63505,1063503,64010,1064008,64517,1064515,65026,1065024,65537,1065535,66050,1066048,66565,1066563,67082,1067080,67601,1067599,68122,1068120,68645,1068643,69170,1069168,69697,1069695,70226,1070224,70757,1070755,71290,1071288,71825,1071823,72362,1072360,72901,1072899,73442,1073440,73985,1073983,74530,1074528,75077,1075075,75626,1075624,76177,1076175,76730,1076728,77285,1077283,77842,1077840,78401,1078399,78962,1078960,79525,1079523,80090,1080088,80657,1080655,81226,1081224,81797,1081795,82370,1082368,82945,1082943,83522,1083520,84101,1084099,84682,1084680,85265,1085263,85850,1085848,86437,1086435,87026,1087024,87617,1087615,88210,1088208,88805,1088803,89402,1089400,90001,1089999,90602,1090600,91205,1091203,91810,1091808,92417,1092415,93026,1093024,93637,1093635,94250,1094248,94865,1094863,95482,1095480,96101,1096099,96722,1096720,97345,1097343,97970,1097968,98597,1098595,99226,1099224,99857,1099855,100490,1100488,101125,1101123,101762,1101760,102401,1102399,103042,1103040,103685,1103683,104330,1104328,104977,1104975,105626,1105624,106277,1106275,106930,1106928,107585,1107583,108242,1108240,108901,1108899,109562,1109560,110225,1110223,110890,1110888,111557,1111555,112226,1112224,112897,1112895,113570,1113568,114245,1114243,114922,1114920,115601,1115599,116282,1116280,116965,1116963,117650,1117648,118337,1118335,119026,1119024,119717,1119715,120410,1120408,121105,1121103,121802,1121800,122501,1122499,123202,1123200,123905,1123903,124610,1124608,125317,1125315,126026,1126024,126737,1126735,127450,1127448,128165,1128163,128882,1128880,129601,1129599,130322,1130320,131045,1131043,131770,1131768,132497,1132495,133226,1133224,133957,1133955,134690,1134688,135425,1135423,136162,1136160,136901,1136899,137642,1137640,138385,1138383,139130,1139128,139877,1139875,140626,1140624,141377,1141375,142130,1142128,142885,1142883,143642,1143640,144401,1144399,145162,1145160,145925,1145923,146690,1146688,147457,1147455,148226,1148224,148997,1148995,149770,1149768,150545,1150543,151322,1151320,152101,1152099,152882,1152880,153665,1153663,154450,1154448,155237,1155235,156026,1156024,156817,1156815,157610,1157608,158405,1158403,159202,1159200,160001,1159999,160802,1160800,161605,1161603,162410,1162408,163217,1163215,164026,1164024,164837,1164835,165650,1165648,166465,1166463,167282,1167280,168101,1168099,168922,1168920,169745,1169743,170570,1170568,171397,1171395,172226,1172224,173057,1173055,173890,1173888,174725,1174723,175562,1175560,176401,1176399,177242,1177240,178085,1178083,178930,1178928,179777,1179775,180626,1180624,181477,1181475,182330,1182328,183185,1183183,184042,1184040,184901,1184899,185762,1185760,186625,1186623,187490,1187488,188357,1188355,189226,1189224,190097,1190095,190970,1190968,191845,1191843,192722,1192720,193601,1193599,194482,1194480,195365,1195363,196250,1196248,197137,1197135,198026,1198024,198917,1198915,199810,1199808,200705,1200703,201602,1201600,202501,1202499,203402,1203400,204305,1204303,205210,1205208,206117,1206115,207026,1207024,207937,1207935,208850,1208848,209765,1209763,210682,1210680,211601,1211599,212522,1212520,213445,1213443,214370,1214368,215297,1215295,216226,1216224,217157,1217155,218090,1218088,219025,1219023,219962,1219960,220901,1220899,221842,1221840,222785,1222783,223730,1223728,224677,1224675,225626,1225624,226577,1226575,227530,1227528,228485,1228483,229442,1229440,230401,1230399,231362,1231360,232325,1232323,233290,1233288,234257,1234255,235226,1235224,236197,1236195,237170,1237168,238145,1238143,239122,1239120,240101,1240099,241082,1241080,242065,1242063,243050,1243048,244037,1244035,245026,1245024,246017,1246015,247010,1247008,248005,1248003,249002,1249000,250001,1249999,251002,1251000,252005,1252003,253010,1253008,254017,1254015,255026,1255024,256037,1256035,257050,1257048,258065,1258063,259082,1259080,260101,1260099,261122,1261120,262145,1262143,263170,1263168,264197,1264195,265226,1265224,266257,1266255,267290,1267288,268325,1268323,269362,1269360,270401,1270399,271442,1271440,272485,1272483,273530,1273528,274577,1274575,275626,1275624,276677,1276675,277730,1277728,278785,1278783,279842,1279840,280901,1280899,281962,1281960,283025,1283023,284090,1284088,285157,1285155,286226,1286224,287297,1287295,288370,1288368,289445,1289443,290522,1290520,291601,1291599,292682,1292680,293765,1293763,294850,1294848,295937,1295935,297026,1297024,298117,1298115,299210,1299208,300305,1300303,301402,1301400,302501,1302499,303602,1303600,304705,1304703,305810,1305808,306917,1306915,308026,1308024,309137,1309135,310250,1310248,311365,1311363,312482,1312480,313601,1313599,314722,1314720,315845,1315843,316970,1316968,318097,1318095,319226,1319224,320357,1320355,321490,1321488,322625,1322623,323762,1323760,324901,1324899,326042,1326040,327185,1327183,328330,1328328,329477,1329475,330626,1330624,331777,1331775,332930,1332928,334085,1334083,335242,1335240,336401,1336399,337562,1337560,338725,1338723,339890,1339888,341057,1341055,342226,1342224,343397,1343395,344570,1344568,345745,1345743,346922,1346920,348101,1348099,349282,1349280,350465,1350463,351650,1351648,352837,1352835,354026,1354024,355217,1355215,356410,1356408,357605,1357603,358802,1358800,360001,1359999,361202,1361200,362405,1362403,363610,1363608,364817,1364815,366026,1366024,367237,1367235,368450,1368448,369665,1369663,370882,1370880,372101,1372099,373322,1373320,374545,1374543,375770,1375768,376997,1376995,378226,1378224,379457,1379455,380690,1380688,381925,1381923,383162,1383160,384401,1384399,385642,1385640,386885,1386883,388130,1388128,389377,1389375,390626,1390624,391877,1391875,393130,1393128,394385,1394383,395642,1395640,396901,1396899,398162,1398160,399425,1399423,400690,1400688,401957,1401955,403226,1403224,404497,1404495,405770,1405768,407045,1407043,408322,1408320,409601,1409599,410882,1410880,412165,1412163,413450,1413448,414737,1414735,416026,1416024,417317,1417315,418610,1418608,419905,1419903,421202,1421200,422501,1422499,423802,1423800,425105,1425103,426410,1426408,427717,1427715,429026,1429024,430337,1430335,431650,1431648,432965,1432963,434282,1434280,435601,1435599,436922,1436920,438245,1438243,439570,1439568,440897,1440895,442226,1442224,443557,1443555,444890,1444888,446225,1446223,447562,1447560,448901,1448899,450242,1450240,451585,1451583,452930,1452928,454277,1454275,455626,1455624,456977,1456975,458330,1458328,459685,1459683,461042,1461040,462401,1462399,463762,1463760,465125,1465123,466490,1466488,467857,1467855,469226,1469224,470597,1470595,471970,1471968,473345,1473343,474722,1474720,476101,1476099,477482,1477480,478865,1478863,480250,1480248,481637,1481635,483026,1483024,484417,1484415,485810,1485808,487205,1487203,488602,1488600,490001,1489999,491402,1491400,492805,1492803,494210,1494208,495617,1495615,497026,1497024,498437,1498435,499850,1499848,501265,1501263,502682,1502680,504101,1504099,505522,1505520,506945,1506943,508370,1508368,509797,1509795,511226,1511224,512657,1512655,514090,1514088,515525,1515523,516962,1516960,518401,1518399,519842,1519840,521285,1521283,522730,1522728,524177,1524175,525626,1525624,527077,1527075,528530,1528528,529985,1529983,531442,1531440,532901,1532899,534362,1534360,535825,1535823,537290,1537288,538757,1538755,540226,1540224,541697,1541695,543170,1543168,544645,1544643,546122,1546120,547601,1547599,549082,1549080,550565,1550563,552050,1552048,553537,1553535,555026,1555024,556517,1556515,558010,1558008,559505,1559503,561002,1561000,562501,1562499,564002,1564000,565505,1565503,567010,1567008,568517,1568515,570026,1570024,571537,1571535,573050,1573048,574565,1574563,576082,1576080,577601,1577599,579122,1579120,580645,1580643,582170,1582168,583697,1583695,585226,1585224,586757,1586755,588290,1588288,589825,1589823,591362,1591360,592901,1592899,594442,1594440,595985,1595983,597530,1597528,599077,1599075,600626,1600624,602177,1602175,603730,1603728,605285,1605283,606842,1606840,608401,1608399,609962,1609960,611525,1611523,613090,1613088,614657,1614655,616226,1616224,617797,1617795,619370,1619368,620945,1620943,622522,1622520,624101,1624099,625682,1625680,627265,1627263,628850,1628848,630437,1630435,632026,1632024,633617,1633615,635210,1635208,636805,1636803,638402,1638400,640001,1639999,641602,1641600,643205,1643203,644810,1644808,646417,1646415,648026,1648024,649637,1649635,651250,1651248,652865,1652863,654482,1654480,656101,1656099,657722,1657720,659345,1659343,660970,1660968,662597,1662595,664226,1664224,665857,1665855,667490,1667488,669125,1669123,670762,1670760,672401,1672399,674042,1674040,675685,1675683,677330,1677328,678977,1678975,680626,1680624,682277,1682275,683930,1683928,685585,1685583,687242,1687240,688901,1688899,690562,1690560,692225,1692223,693890,1693888,695557,1695555,697226,1697224,698897,1698895,700570,1700568,702245,1702243,703922,1703920,705601,1705599,707282,1707280,708965,1708963,710650,1710648,712337,1712335,714026,1714024,715717,1715715,717410,1717408,719105,1719103,720802,1720800,722501,1722499,724202,1724200,725905,1725903,727610,1727608,729317,1729315,731026,1731024,732737,1732735,734450,1734448,736165,1736163,737882,1737880,739601,1739599,741322,1741320,743045,1743043,744770,1744768,746497,1746495,748226,1748224,749957,1749955,751690,1751688,753425,1753423,755162,1755160,756901,1756899,758642,1758640,760385,1760383,762130,1762128,763877,1763875,765626,1765624,767377,1767375,769130,1769128,770885,1770883,772642,1772640,774401,1774399,776162,1776160,777925,1777923,779690,1779688,781457,1781455,783226,1783224,784997,1784995,786770,1786768,788545,1788543,790322,1790320,792101,1792099,793882,1793880,795665,1795663,797450,1797448,799237,1799235,801026,1801024,802817,1802815,804610,1804608,806405,1806403,808202,1808200,810001,1809999,811802,1811800,813605,1813603,815410,1815408,817217,1817215,819026,1819024,820837,1820835,822650,1822648,824465,1824463,826282,1826280,828101,1828099,829922,1829920,831745,1831743,833570,1833568,835397,1835395,837226,1837224,839057,1839055,840890,1840888,842725,1842723,844562,1844560,846401,1846399,848242,1848240,850085,1850083,851930,1851928,853777,1853775,855626,1855624,857477,1857475,859330,1859328,861185,1861183,863042,1863040,864901,1864899,866762,1866760,868625,1868623,870490,1870488,872357,1872355,874226,1874224,876097,1876095,877970,1877968,879845,1879843,881722,1881720,883601,1883599,885482,1885480,887365,1887363,889250,1889248,891137,1891135,893026,1893024,894917,1894915,896810,1896808,898705,1898703,900602,1900600,902501,1902499,904402,1904400,906305,1906303,908210,1908208,910117,1910115,912026,1912024,913937,1913935,915850,1915848,917765,1917763,919682,1919680,921601,1921599,923522,1923520,925445,1925443,927370,1927368,929297,1929295,931226,1931224,933157,1933155,935090,1935088,937025,1937023,938962,1938960,940901,1940899,942842,1942840,944785,1944783,946730,1946728,948677,1948675,950626,1950624,952577,1952575,954530,1954528,956485,1956483,958442,1958440,960401,1960399,962362,1962360,964325,1964323,966290,1966288,968257,1968255,970226,1970224,972197,1972195,974170,1974168,976145,1976143,978122,1978120,980101,1980099,982082,1982080,984065,1984063,986050,1986048,988037,1988035,990026,1990024,992017,1992015,994010,1994008,996005,1996003,998002,1998000]

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    unordered_map<int, list<int>> buildEleIndsMap(vector<int>& sortedVec) {
        unordered_map<int, list<int>> eleIndsMap;
        for (int i = 0; i < sortedVec.size(); i++) {
            eleIndsMap[sortedVec[i]].push_back(i);
        }

        return eleIndsMap;
    }

    void showVec(vector<int>& vec, string name) {
        printf("\n%s (int) vec is:-\n", name.c_str());

        printf("Ind\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    void showVec(vector<bool>& vec, string name) {
        printf("\n%s (bool) vec is:-\n", name.c_str());

        printf("Ind\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%s\t", (vec[i] ? "true" : "false"));
        }
        cout << endl;
    }

    bool isValid(vector<int>& sortedVec, unordered_map<int, list<int>> eleIndsMap, int k) {
        int len = sortedVec.size();
        if (len == 0) {
            return true;
        }
        if ((len % 2) == 1) {
            return false;
        }

        vector<bool> consumed(len, false);
        int numConsumed = 0;
        for (int i = 0; (i < len) && (numConsumed < len); i++) {
            if (debug) {
                printf("\n--------\n");
                showVec(sortedVec, "sortedVec");
                showVec(consumed, "consumed");
                printf("\nat sortedVec[i=%d]=%d, k=%d\n\n", i, sortedVec[i], k);
            }

            if (consumed[i]) {
                if (debug) {
                    printf("skipping as sortedVec[i=%d]=%d is already consumed\n", i, sortedVec[i]);
                }
                continue;
            }

            int crrEle = sortedVec[i];
            int reqEle = crrEle + 2 * k;

            bool hasReqEle = eleIndsMap.find(reqEle) != eleIndsMap.end();
            int reqEleInd = hasReqEle ? (eleIndsMap[reqEle].front()) : -1;
            if (hasReqEle && !consumed[reqEleInd]) {
                if (debug) {
                    printf("consuming crrEle:sortedVec[%d]=%d and reqEle:sortedVec[%d]=%d\n", i, sortedVec[i], reqEleInd, reqEle);
                }
                numConsumed += 2;
                consumed[i] = true;
                consumed[reqEleInd] = true;
                eleIndsMap[reqEle].pop_front();
            } else {
                if (debug) {
                    printf("skipping consuming crrEle=%d and reqEle=%d\n", crrEle, reqEle);
                }
            }
        }

        return (numConsumed == len);
    }

    vector<int> recoverVec(vector<int>& sortedVec, unordered_map<int, list<int>>& eleIndsMap, int k) {
        int len = sortedVec.size();
        if (len == 0) {
            return {};
        }
        if ((len % 2) == 1) {
            return {};
        }

        vector<int> recoveredVec;
        vector<bool> consumed(len, false);
        int numConsumed = 0;
        for (int i = 0; (i < len) && (numConsumed < len); i++) {
            if (debug) {
                printf("\n--------\n");
                showVec(sortedVec, "sortedVec");
                showVec(consumed, "consumed");
                printf("\nat sortedVec[i=%d]=%d, k=%d\n\n", i, sortedVec[i], k);
            }

            int crrEle = sortedVec[i];
            if (consumed[i]) {
                if (debug) {
                    printf("skipping as sortedVec[i=%d]=%d is already consumed\n", i, sortedVec[i]);
                }
                continue;
            }

            int reqEle = crrEle + 2 * k;

            bool hasReqEle = eleIndsMap.find(reqEle) != eleIndsMap.end();
            int reqEleInd = hasReqEle ? (eleIndsMap[reqEle].front()) : -1;
            if (hasReqEle && !consumed[reqEleInd]) {
                numConsumed += 2;
                consumed[i] = true;
                consumed[reqEleInd] = true;
                eleIndsMap[reqEle].pop_front();

                int orgEle = crrEle + k;
                recoveredVec.push_back(orgEle);
            }
        }

        if (numConsumed == len) {
            return recoveredVec;
        } else {
            return {};
        }
    }

    vector<int> findCandidateKVals(vector<int>& sortedVec) {
        int len = sortedVec.size();

        vector<int> candKVals;
        for (int i = 1; i <= (len / 2); i++) {
            int diff = sortedVec[i] - sortedVec[0];
            if (((diff % 2) == 1) || (diff == 0)) {
                continue;
            }
            candKVals.push_back(diff / 2);
        }

        return candKVals;
    }

   public:
    friend class SolutionTest;

    vector<int> recoverArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) {
            return nums;
        }
        if ((len % 2) == 1) {
            return nums;
        }

        sort(nums.begin(), nums.end());
        unordered_map<int, list<int>> eleIndsMap = buildEleIndsMap(nums);

        // int kMin = max((nums[1] - nums[0]) / 2, 1);
        // int kMax = (nums[len / 2] - nums[0]) / 2;
        // for (int k = kMin; k <= kMax; k++) {
        //     if (isValid(nums, eleIndsMap, k)) {
        //         return recoverVec(nums, eleIndsMap, k);
        //     } else {
        //         if (debug) {
        //             printf("k=%d is NOT valid\n", k);
        //         }
        //     }
        // }

        vector<int> candKVals = findCandidateKVals(nums);
        for (int i = 0; i < candKVals.size(); i++) {
            int k = candKVals[i];
            if (isValid(nums, eleIndsMap, k)) {
                return recoverVec(nums, eleIndsMap, k);
            }
        }

        return nums;
    }
};

class SolutionTest {
   public:
    void testIsValid() {
        Solution soln = Solution();
        vector<int> inVec;
        unordered_map<int, list<int>> inEleIndsMap;
        int inK;
        bool outExpected;
        bool outComputed;

        inVec = {};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 5;
        outExpected = true;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);

        inVec = {5};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 5;
        outExpected = false;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);

        // soln.debug = true;
        inVec = {2, 4, 6, 8, 10, 12};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 1;
        outExpected = true;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {2, 4, 6, 8, 10, 12};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 2;
        outExpected = false;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {2, 4, 6, 8, 10, 12};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 3;
        outExpected = true;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {1, 1, 3, 3};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 1;
        outExpected = true;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {5, 435};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 215;
        outExpected = true;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {5, 435};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 214;
        outExpected = false;
        outComputed = soln.isValid(inVec, inEleIndsMap, inK);
        assert(outExpected == outComputed);
        // soln.debug = false;
    }

    void testRecoverVec() {
        Solution soln = Solution();
        vector<int> inVec;
        unordered_map<int, list<int>> inEleIndsMap;
        int inK;
        vector<int> outVecExpected;
        vector<int> outVecComputed;

        inVec = {};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 5;
        outVecExpected = {};
        outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        assert(outVecExpected == outVecComputed);

        // inVec = {5};
        // inEleIndsMap = soln.buildEleIndsMap(inVec);
        // inK = 5;
        // outVecExpected = false;
        // outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        // assert(outVecExpected == outVecComputed);

        // soln.debug = true;
        inVec = {2, 4, 6, 8, 10, 12};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 1;
        outVecExpected = {3, 7, 11};
        outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        inVec = {2, 4, 6, 8, 10, 12};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 3;
        outVecExpected = {5, 7, 9};
        outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        assert(outVecExpected == outVecComputed);

        // soln.debug = true;
        // inVec = {2, 4, 6, 8, 10, 12};
        // inEleIndsMap = soln.buildEleIndsMap(inVec);
        // inK = 2;
        // outVecExpected = false;
        // outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        // assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {1, 1, 3, 3};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 1;
        outVecExpected = {2, 2};
        outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        // soln.showVec(outVecComputed, "outVecComputed");
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {5, 435};
        inEleIndsMap = soln.buildEleIndsMap(inVec);
        inK = 215;
        outVecExpected = {220};
        outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        // soln.debug = true;
        // inVec = {5, 435};
        // inEleIndsMap = soln.buildEleIndsMap(inVec);
        // inK = 214;
        // outVecExpected = false;
        // outVecComputed = soln.recoverVec(inVec, inEleIndsMap, inK);
        // assert(outVecExpected == outVecComputed);
        // soln.debug = false;
    }

    void testRecoverArray() {
        Solution soln = Solution();
        vector<int> inVec;
        vector<int> outVecExpected;
        vector<int> outVecComputed;

        // soln.debug = true;
        inVec = {2, 10, 6, 4, 8, 12};
        outVecExpected = {3, 7, 11};
        outVecComputed = soln.recoverArray(inVec);
        // soln.showVec(outVecComputed, "outVecComputed");
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {1, 3, 3, 1};
        outVecExpected = {2, 2};
        outVecComputed = soln.recoverArray(inVec);
        // soln.showVec(outVecComputed, "outVecComputed");
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        inVec = {435, 5};
        outVecExpected = {220};
        outVecComputed = soln.recoverArray(inVec);
        assert(outVecExpected == outVecComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testIsValid();
    solnTest.testRecoverVec();
    solnTest.testRecoverArray();

    return 0;
}
