inpath="/hdfs/store/user/htsoi/haabbtt_selection/haabbtt_mt2017_7sep"
outpath="outputs/mt_2017"
exe="selection_mt_allyears.exe"
#./$exe $inpath/embedded.root $outpath/embedded.root embedded ZTT 2017
./$exe $inpath/DY.root $outpath/DY.root DY Z 2017
./$exe $inpath/DY1.root $outpath/DY1.root DY1 Z 2017
./$exe $inpath/DY2.root $outpath/DY2.root DY2 Z 2017
./$exe $inpath/DY3.root $outpath/DY3.root DY3 Z 2017
./$exe $inpath/DY4.root $outpath/DY4.root DY4 Z 2017
./$exe $inpath/GGHTT.root $outpath/GGHTT.root GGHTT HTT 2017
./$exe $inpath/GGHWW.root $outpath/GGHWW.root GGHWW HWW 2017
./$exe $inpath/GGZHLLTT.root $outpath/GGZHLLTT.root GGZHLLTT HTT 2017
./$exe $inpath/GGZHNNTT.root $outpath/GGZHNNTT.root GGZHNNTT HTT 2017
./$exe $inpath/GGZHQQTT.root $outpath/GGZHQQTT.root GGZHQQTT HTT 2017
./$exe $inpath/GGZHWW.root $outpath/GGZHWW.root GGZHWW HWW 2017
./$exe $inpath/ST_tW_antitop.root $outpath/ST_tW_antitop.root ST_tW_antitop ST 2017
./$exe $inpath/ST_tW_top.root $outpath/ST_tW_top.root ST_tW_top ST 2017
./$exe $inpath/ST_t_antitop.root $outpath/ST_t_antitop.root ST_t_antitop ST 2017
./$exe $inpath/ST_t_top.root $outpath/ST_t_top.root ST_t_top ST 2017
./$exe $inpath/TTTo2L2Nu.root $outpath/TTTo2L2Nu.root TTTo2L2Nu TT 2017
./$exe $inpath/TTToHadronic.root $outpath/TTToHadronic.root TTToHadronic TT 2017
#./$exe $inpath/TTToSemiLeptonic.root $outpath/TTToSemiLeptonic.root TTToSemiLeptonic TT 2017
./$exe $inpath/VBFHTT.root $outpath/VBFHTT.root VBFHTT HTT 2017
./$exe $inpath/VBFHWW.root $outpath/VBFHWW.root VBFHWW HWW 2017
./$exe $inpath/VV2L2Nu.root $outpath/VV2L2Nu.root VV2L2Nu VV 2017
#./$exe $inpath/W.root $outpath/W.root W W 2017
#./$exe $inpath/W1.root $outpath/W1.root W1 W 2017
#./$exe $inpath/W2.root $outpath/W2.root W2 W 2017
#./$exe $inpath/W3.root $outpath/W3.root W3 W 2017
#./$exe $inpath/W4.root $outpath/W4.root W4 W 2017
./$exe $inpath/WZ2L2Q.root $outpath/WZ2L2Q.root WZ2L2Q VV 2017
./$exe $inpath/WZ3L1Nu.root $outpath/WZ3L1Nu.root WZ3L1Nu VV 2017
./$exe $inpath/WminusHTT.root $outpath/WminusHTT.root WminusHTT HTT 2017
./$exe $inpath/WminusHWW.root $outpath/WminusHWW.root WminusHWW HWW 2017
./$exe $inpath/WplusHTT.root $outpath/WplusHTT.root WplusHTT HTT 2017
./$exe $inpath/WplusHWW.root $outpath/WplusHWW.root WplusHWW HWW 2017
./$exe $inpath/ZHTT.root $outpath/ZHTT.root ZHTT HTT 2017
./$exe $inpath/ZHWW.root $outpath/ZHWW.root ZHWW HWW 2017
./$exe $inpath/ZZ2L2Q.root $outpath/ZZ2L2Q.root ZZ2L2Q VV 2017
./$exe $inpath/ZZ4L.root $outpath/ZZ4L.root ZZ4L VV 2017
./$exe $inpath/ttHnonbb.root $outpath/ttHnonbb.root ttHnonbb ttHnonbb 2017
#./$exe $inpath/data_obs.root $outpath/data_obs.root data_obs data_obs 2017

./$exe $inpath/ggH_bbtt12.root $outpath/gghbbtt12.root gghbbtt12 gghbbtt12 2017
./$exe $inpath/ggH_bbtt20.root $outpath/gghbbtt20.root gghbbtt20 gghbbtt20 2017
./$exe $inpath/ggH_bbtt30.root $outpath/gghbbtt30.root gghbbtt30 gghbbtt30 2017
./$exe $inpath/ggH_bbtt40.root $outpath/gghbbtt40.root gghbbtt40 gghbbtt40 2017
./$exe $inpath/ggH_bbtt50.root $outpath/gghbbtt50.root gghbbtt50 gghbbtt50 2017
./$exe $inpath/ggH_bbtt60.root $outpath/gghbbtt60.root gghbbtt60 gghbbtt60 2017
./$exe $inpath/vbf_bbtt12.root $outpath/vbfbbtt12.root vbfbbtt12 vbfbbtt12 2017
./$exe $inpath/vbf_bbtt20.root $outpath/vbfbbtt20.root vbfbbtt20 vbfbbtt20 2017
./$exe $inpath/vbf_bbtt30.root $outpath/vbfbbtt30.root vbfbbtt30 vbfbbtt30 2017
./$exe $inpath/vbf_bbtt40.root $outpath/vbfbbtt40.root vbfbbtt40 vbfbbtt40 2017
./$exe $inpath/vbf_bbtt50.root $outpath/vbfbbtt50.root vbfbbtt50 vbfbbtt50 2017
./$exe $inpath/vbf_bbtt60.root $outpath/vbfbbtt60.root vbfbbtt60 vbfbbtt60 2017

#hadd -f $outpath/final_mt_2017.root $outpath/*.root
