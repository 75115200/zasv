
测试项目说明

| action| count| total(ns)| avg(ns) |
| :--- |
|java add(0xffff+ 1) | 1M | 调用1M次java写的add方法 | 每次调用 |
|cpp add(0xffff+ 1) | 1M |
|javaBatchAdd(0xffff+ 1) 1K| 1K | javaBatchAdd 内部直接循环计算1k次， 调用javaBatchAdd 1K次 | 总时间 / (1k * 1k) 即每次加运算的时间 |
|cppBatchAdd(0xffff+ 1) 1K| 1K |
|javaBatchMemcpy(1M) | 1K | 循环 用System.arrayCopy 复制 1M 大的数据 1k次 | 每个循环 |
|cppBatchMemcpy(1M) | 1K | 循环 用memcpy 复制 1M 大的数据 1k次 | 每个循环 |
|javaBatchMemset(1M) | 1K | 循环 用遍历数组的方式把1M数组每一个item都至为1 共 1k次 | 每个循环
|cppBatchMemset(1M) | 1K | 循环 memset的方式把1M数组每一个item都至为1 共 1k次 | 每个循环
|passByteArrayToNative(1M) | 1K | JNI方法，传一个java数字给native，native拿到把数组每一位都置为1， 调用1k次 | 每次调用 |
|passByteBufferToNative(1M) | 1K | 同上，传递的是DirectByteBuffer | 每次调用 |
|javaReadDirectBuffer(1M) | 1K | java 循环 从 directByteBuffer中读取1M数据 1k次 | 每次循环 |


device Nexus 4 MAKO API-22

| action| count| total(ns)| avg(ns) |
| :--- |
|java add(0xffff+ 1) | 1M |18434305| 17|
|cpp add(0xffff+ 1) | 1M |605249503| 577|
|javaBatchAdd(0xffff+ 1) 1K| 1K |4394934| 4|
|cppBatchAdd(0xffff+ 1) 1K| 1K |12452311| 11|
|javaBatchMemcpy(1M) | 1K |212055547| 202|
|cppBatchMemcpy(1M) | 1K |140729437| 134|
|javaBatchMemset(1M) | 1K |5253746375| 5130611|
|cppBatchMemset(1M) | 1K |85365482| 83364|
|passByteArrayToNative(1M) | 1K |176377247| 172243|
|passByteBufferToNative(1M) | 1K |240408978| 234774|
|javaReadDirectBuffer(1M) | 1K |337677403| 329763|

结论，对比javaAdd 和cppAdd的结果发现 JNI调用比普通的java调用耗时增加,可以认为是500+ns
然后是batchAdd方面，ART下java的性能比c还要好。
memcpy略有差别。
java的没有memset之类的批处理方法，因此遍历数组set值，性能很差，意料之中
相比之下，不管是byte[]还是DirectByteBuffer传到native再set都比java中做性能好一个数量级。



device Nexus 4 MAKO API-19

|action| count| total(ns)| avg(ns)
| :--- |
|java add(0xffff+ 1) | 1M |302734375| 288|
|cpp add(0xffff+ 1) | 1M |575439452| 548|
|javaBatchAdd(0xffff+ 1) 1K| 1K |122192384| 116|
|cppBatchAdd(0xffff+ 1) 1K| 1K |12512207| 11|
|javaBatchMemcpy(1M) | 1K |430725098| 410|
|cppBatchMemcpy(1M) | 1K |194519042| 185|
|javaBatchMemset(1M) | 1K |10177581788| 9939044|
|cppBatchMemset(1M) | 1K |157653806| 153958|
|javaReadDirectBuffer(1M) | 1K |372161872| 363439|
|passByteArrayToNative(1M) | 1K |256622315| 250607|
|passByteBufferToNative(1M) | 1K |222412083| 217199|


* * *


device Nexus 4 MAKO API-22

|action| count| total(ns)| avg(ns)
| :--- |
|java add(0xffff+ 1) | 1M |18312223| 17|
|cpp add(0xffff+ 1) | 1M |586967801| 559|
|javaBatchAdd(0xffff+ 1) 1K| 1K |4455974| 4|
|cppBatchAdd(0xffff+ 1) 1K| 1K |12421791| 11|
|javaBatchMemcpy(1M) | 1K |147443921| 140|
|cppBatchMemcpy(1M) | 1K |152174578| 145|
|javaBatchMemset(1M) | 1K |5330260948| 5205332|
|cppBatchMemset(1M) | 1K |95833968| 93587|
|passByteArrayToNative(1M) | 1K |193865413| 189321|
|passByteBufferToNative(1M) | 1K |230398295| 224998|
|javaReadDirectBuffer(1M) | 1K |335693584| 327825|

device Nexus 4 MAKO API-19

|action| count| total(ns)| avg(ns)
| :--- |
|java add(0xffff+ 1) | 1M |279602053| 266|
|cpp add(0xffff+ 1) | 1M |625122071| 596|
|javaBatchAdd(0xffff+ 1) 1K| 1K |149139405| 142|
|cppBatchAdd(0xffff+ 1) 1K| 1K |17059326| 16|
|javaBatchMemcpy(1M) | 1K |437255862| 416|
|cppBatchMemcpy(1M) | 1K |167480468| 159|
|javaBatchMemset(1M) | 1K |10154968263| 9916961|
|cppBatchMemset(1M) | 1K |88806152| 86724|
|passByteArrayToNative(1M) | 1K |244873043| 239133|
|passByteBufferToNative(1M) | 1K |218017563| 212907|
|javaReadDirectBuffer(1M) | 1K |419464112| 409632|
