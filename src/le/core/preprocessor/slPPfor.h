#ifndef H_slPPfor_included
#define H_slPPfor_included

// predicate - macro of type PREDICATE(current) must expand to 1 or 0
// action - macro of type ACTION(current)

#include "slPPbit_if.h"

#define LE_PP_FOR(initial, predicate, action) _LE_PP_FOR_(initial, predicate, action)

#define _LE_PP_FOR_(initial, predicate, action) _LE_PP_FOR_##initial(predicate, action)

#define _LE_PP_NOTHING


#define _LE_PP_FOR_0(_p, _a) LE_PP_BIT_IF(_p(0), _a(0) _LE_PP_FOR_1(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_1(_p, _a) LE_PP_BIT_IF(_p(1), _a(1) _LE_PP_FOR_2(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_2(_p, _a) LE_PP_BIT_IF(_p(2), _a(2) _LE_PP_FOR_3(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_3(_p, _a) LE_PP_BIT_IF(_p(3), _a(3) _LE_PP_FOR_4(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_4(_p, _a) LE_PP_BIT_IF(_p(4), _a(4) _LE_PP_FOR_5(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_5(_p, _a) LE_PP_BIT_IF(_p(5), _a(5) _LE_PP_FOR_6(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_6(_p, _a) LE_PP_BIT_IF(_p(6), _a(6) _LE_PP_FOR_7(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_7(_p, _a) LE_PP_BIT_IF(_p(7), _a(7) _LE_PP_FOR_8(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_8(_p, _a) LE_PP_BIT_IF(_p(8), _a(8) _LE_PP_FOR_9(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_9(_p, _a) LE_PP_BIT_IF(_p(9), _a(9) _LE_PP_FOR_10(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_10(_p, _a) LE_PP_BIT_IF(_p(10), _a(10) _LE_PP_FOR_11(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_11(_p, _a) LE_PP_BIT_IF(_p(11), _a(11) _LE_PP_FOR_12(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_12(_p, _a) LE_PP_BIT_IF(_p(12), _a(12) _LE_PP_FOR_13(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_13(_p, _a) LE_PP_BIT_IF(_p(13), _a(13) _LE_PP_FOR_14(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_14(_p, _a) LE_PP_BIT_IF(_p(14), _a(14) _LE_PP_FOR_15(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_15(_p, _a) LE_PP_BIT_IF(_p(15), _a(15) _LE_PP_FOR_16(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_16(_p, _a) LE_PP_BIT_IF(_p(16), _a(16) _LE_PP_FOR_17(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_17(_p, _a) LE_PP_BIT_IF(_p(17), _a(17) _LE_PP_FOR_18(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_18(_p, _a) LE_PP_BIT_IF(_p(18), _a(18) _LE_PP_FOR_19(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_19(_p, _a) LE_PP_BIT_IF(_p(19), _a(19) _LE_PP_FOR_20(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_20(_p, _a) LE_PP_BIT_IF(_p(20), _a(20) _LE_PP_FOR_21(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_21(_p, _a) LE_PP_BIT_IF(_p(21), _a(21) _LE_PP_FOR_22(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_22(_p, _a) LE_PP_BIT_IF(_p(22), _a(22) _LE_PP_FOR_23(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_23(_p, _a) LE_PP_BIT_IF(_p(23), _a(23) _LE_PP_FOR_24(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_24(_p, _a) LE_PP_BIT_IF(_p(24), _a(24) _LE_PP_FOR_25(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_25(_p, _a) LE_PP_BIT_IF(_p(25), _a(25) _LE_PP_FOR_26(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_26(_p, _a) LE_PP_BIT_IF(_p(26), _a(26) _LE_PP_FOR_27(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_27(_p, _a) LE_PP_BIT_IF(_p(27), _a(27) _LE_PP_FOR_28(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_28(_p, _a) LE_PP_BIT_IF(_p(28), _a(28) _LE_PP_FOR_29(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_29(_p, _a) LE_PP_BIT_IF(_p(29), _a(29) _LE_PP_FOR_30(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_30(_p, _a) LE_PP_BIT_IF(_p(30), _a(30) _LE_PP_FOR_31(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_31(_p, _a) LE_PP_BIT_IF(_p(31), _a(31) _LE_PP_FOR_32(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_32(_p, _a) LE_PP_BIT_IF(_p(32), _a(32) _LE_PP_FOR_33(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_33(_p, _a) LE_PP_BIT_IF(_p(33), _a(33) _LE_PP_FOR_34(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_34(_p, _a) LE_PP_BIT_IF(_p(34), _a(34) _LE_PP_FOR_35(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_35(_p, _a) LE_PP_BIT_IF(_p(35), _a(35) _LE_PP_FOR_36(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_36(_p, _a) LE_PP_BIT_IF(_p(36), _a(36) _LE_PP_FOR_37(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_37(_p, _a) LE_PP_BIT_IF(_p(37), _a(37) _LE_PP_FOR_38(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_38(_p, _a) LE_PP_BIT_IF(_p(38), _a(38) _LE_PP_FOR_39(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_39(_p, _a) LE_PP_BIT_IF(_p(39), _a(39) _LE_PP_FOR_40(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_40(_p, _a) LE_PP_BIT_IF(_p(40), _a(40) _LE_PP_FOR_41(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_41(_p, _a) LE_PP_BIT_IF(_p(41), _a(41) _LE_PP_FOR_42(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_42(_p, _a) LE_PP_BIT_IF(_p(42), _a(42) _LE_PP_FOR_43(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_43(_p, _a) LE_PP_BIT_IF(_p(43), _a(43) _LE_PP_FOR_44(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_44(_p, _a) LE_PP_BIT_IF(_p(44), _a(44) _LE_PP_FOR_45(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_45(_p, _a) LE_PP_BIT_IF(_p(45), _a(45) _LE_PP_FOR_46(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_46(_p, _a) LE_PP_BIT_IF(_p(46), _a(46) _LE_PP_FOR_47(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_47(_p, _a) LE_PP_BIT_IF(_p(47), _a(47) _LE_PP_FOR_48(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_48(_p, _a) LE_PP_BIT_IF(_p(48), _a(48) _LE_PP_FOR_49(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_49(_p, _a) LE_PP_BIT_IF(_p(49), _a(49) _LE_PP_FOR_50(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_50(_p, _a) LE_PP_BIT_IF(_p(50), _a(50) _LE_PP_FOR_51(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_51(_p, _a) LE_PP_BIT_IF(_p(51), _a(51) _LE_PP_FOR_52(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_52(_p, _a) LE_PP_BIT_IF(_p(52), _a(52) _LE_PP_FOR_53(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_53(_p, _a) LE_PP_BIT_IF(_p(53), _a(53) _LE_PP_FOR_54(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_54(_p, _a) LE_PP_BIT_IF(_p(54), _a(54) _LE_PP_FOR_55(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_55(_p, _a) LE_PP_BIT_IF(_p(55), _a(55) _LE_PP_FOR_56(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_56(_p, _a) LE_PP_BIT_IF(_p(56), _a(56) _LE_PP_FOR_57(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_57(_p, _a) LE_PP_BIT_IF(_p(57), _a(57) _LE_PP_FOR_58(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_58(_p, _a) LE_PP_BIT_IF(_p(58), _a(58) _LE_PP_FOR_59(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_59(_p, _a) LE_PP_BIT_IF(_p(59), _a(59) _LE_PP_FOR_60(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_60(_p, _a) LE_PP_BIT_IF(_p(60), _a(60) _LE_PP_FOR_61(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_61(_p, _a) LE_PP_BIT_IF(_p(61), _a(61) _LE_PP_FOR_62(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_62(_p, _a) LE_PP_BIT_IF(_p(62), _a(62) _LE_PP_FOR_63(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_63(_p, _a) LE_PP_BIT_IF(_p(63), _a(63) _LE_PP_FOR_64(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_64(_p, _a) LE_PP_BIT_IF(_p(64), _a(64) _LE_PP_FOR_65(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_65(_p, _a) LE_PP_BIT_IF(_p(65), _a(65) _LE_PP_FOR_66(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_66(_p, _a) LE_PP_BIT_IF(_p(66), _a(66) _LE_PP_FOR_67(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_67(_p, _a) LE_PP_BIT_IF(_p(67), _a(67) _LE_PP_FOR_68(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_68(_p, _a) LE_PP_BIT_IF(_p(68), _a(68) _LE_PP_FOR_69(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_69(_p, _a) LE_PP_BIT_IF(_p(69), _a(69) _LE_PP_FOR_70(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_70(_p, _a) LE_PP_BIT_IF(_p(70), _a(70) _LE_PP_FOR_71(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_71(_p, _a) LE_PP_BIT_IF(_p(71), _a(71) _LE_PP_FOR_72(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_72(_p, _a) LE_PP_BIT_IF(_p(72), _a(72) _LE_PP_FOR_73(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_73(_p, _a) LE_PP_BIT_IF(_p(73), _a(73) _LE_PP_FOR_74(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_74(_p, _a) LE_PP_BIT_IF(_p(74), _a(74) _LE_PP_FOR_75(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_75(_p, _a) LE_PP_BIT_IF(_p(75), _a(75) _LE_PP_FOR_76(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_76(_p, _a) LE_PP_BIT_IF(_p(76), _a(76) _LE_PP_FOR_77(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_77(_p, _a) LE_PP_BIT_IF(_p(77), _a(77) _LE_PP_FOR_78(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_78(_p, _a) LE_PP_BIT_IF(_p(78), _a(78) _LE_PP_FOR_79(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_79(_p, _a) LE_PP_BIT_IF(_p(79), _a(79) _LE_PP_FOR_80(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_80(_p, _a) LE_PP_BIT_IF(_p(80), _a(80) _LE_PP_FOR_81(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_81(_p, _a) LE_PP_BIT_IF(_p(81), _a(81) _LE_PP_FOR_82(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_82(_p, _a) LE_PP_BIT_IF(_p(82), _a(82) _LE_PP_FOR_83(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_83(_p, _a) LE_PP_BIT_IF(_p(83), _a(83) _LE_PP_FOR_84(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_84(_p, _a) LE_PP_BIT_IF(_p(84), _a(84) _LE_PP_FOR_85(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_85(_p, _a) LE_PP_BIT_IF(_p(85), _a(85) _LE_PP_FOR_86(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_86(_p, _a) LE_PP_BIT_IF(_p(86), _a(86) _LE_PP_FOR_87(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_87(_p, _a) LE_PP_BIT_IF(_p(87), _a(87) _LE_PP_FOR_88(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_88(_p, _a) LE_PP_BIT_IF(_p(88), _a(88) _LE_PP_FOR_89(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_89(_p, _a) LE_PP_BIT_IF(_p(89), _a(89) _LE_PP_FOR_90(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_90(_p, _a) LE_PP_BIT_IF(_p(90), _a(90) _LE_PP_FOR_91(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_91(_p, _a) LE_PP_BIT_IF(_p(91), _a(91) _LE_PP_FOR_92(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_92(_p, _a) LE_PP_BIT_IF(_p(92), _a(92) _LE_PP_FOR_93(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_93(_p, _a) LE_PP_BIT_IF(_p(93), _a(93) _LE_PP_FOR_94(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_94(_p, _a) LE_PP_BIT_IF(_p(94), _a(94) _LE_PP_FOR_95(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_95(_p, _a) LE_PP_BIT_IF(_p(95), _a(95) _LE_PP_FOR_96(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_96(_p, _a) LE_PP_BIT_IF(_p(96), _a(96) _LE_PP_FOR_97(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_97(_p, _a) LE_PP_BIT_IF(_p(97), _a(97) _LE_PP_FOR_98(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_98(_p, _a) LE_PP_BIT_IF(_p(98), _a(98) _LE_PP_FOR_99(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_99(_p, _a) LE_PP_BIT_IF(_p(99), _a(99) _LE_PP_FOR_100(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_100(_p, _a) LE_PP_BIT_IF(_p(100), _a(100) _LE_PP_FOR_101(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_101(_p, _a) LE_PP_BIT_IF(_p(101), _a(101) _LE_PP_FOR_102(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_102(_p, _a) LE_PP_BIT_IF(_p(102), _a(102) _LE_PP_FOR_103(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_103(_p, _a) LE_PP_BIT_IF(_p(103), _a(103) _LE_PP_FOR_104(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_104(_p, _a) LE_PP_BIT_IF(_p(104), _a(104) _LE_PP_FOR_105(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_105(_p, _a) LE_PP_BIT_IF(_p(105), _a(105) _LE_PP_FOR_106(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_106(_p, _a) LE_PP_BIT_IF(_p(106), _a(106) _LE_PP_FOR_107(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_107(_p, _a) LE_PP_BIT_IF(_p(107), _a(107) _LE_PP_FOR_108(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_108(_p, _a) LE_PP_BIT_IF(_p(108), _a(108) _LE_PP_FOR_109(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_109(_p, _a) LE_PP_BIT_IF(_p(109), _a(109) _LE_PP_FOR_110(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_110(_p, _a) LE_PP_BIT_IF(_p(110), _a(110) _LE_PP_FOR_111(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_111(_p, _a) LE_PP_BIT_IF(_p(111), _a(111) _LE_PP_FOR_112(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_112(_p, _a) LE_PP_BIT_IF(_p(112), _a(112) _LE_PP_FOR_113(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_113(_p, _a) LE_PP_BIT_IF(_p(113), _a(113) _LE_PP_FOR_114(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_114(_p, _a) LE_PP_BIT_IF(_p(114), _a(114) _LE_PP_FOR_115(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_115(_p, _a) LE_PP_BIT_IF(_p(115), _a(115) _LE_PP_FOR_116(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_116(_p, _a) LE_PP_BIT_IF(_p(116), _a(116) _LE_PP_FOR_117(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_117(_p, _a) LE_PP_BIT_IF(_p(117), _a(117) _LE_PP_FOR_118(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_118(_p, _a) LE_PP_BIT_IF(_p(118), _a(118) _LE_PP_FOR_119(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_119(_p, _a) LE_PP_BIT_IF(_p(119), _a(119) _LE_PP_FOR_120(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_120(_p, _a) LE_PP_BIT_IF(_p(120), _a(120) _LE_PP_FOR_121(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_121(_p, _a) LE_PP_BIT_IF(_p(121), _a(121) _LE_PP_FOR_122(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_122(_p, _a) LE_PP_BIT_IF(_p(122), _a(122) _LE_PP_FOR_123(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_123(_p, _a) LE_PP_BIT_IF(_p(123), _a(123) _LE_PP_FOR_124(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_124(_p, _a) LE_PP_BIT_IF(_p(124), _a(124) _LE_PP_FOR_125(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_125(_p, _a) LE_PP_BIT_IF(_p(125), _a(125) _LE_PP_FOR_126(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_126(_p, _a) LE_PP_BIT_IF(_p(126), _a(126) _LE_PP_FOR_127(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_127(_p, _a) LE_PP_BIT_IF(_p(127), _a(127) _LE_PP_FOR_128(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_128(_p, _a) LE_PP_BIT_IF(_p(128), _a(128) _LE_PP_FOR_129(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_129(_p, _a) LE_PP_BIT_IF(_p(129), _a(129) _LE_PP_FOR_130(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_130(_p, _a) LE_PP_BIT_IF(_p(130), _a(130) _LE_PP_FOR_131(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_131(_p, _a) LE_PP_BIT_IF(_p(131), _a(131) _LE_PP_FOR_132(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_132(_p, _a) LE_PP_BIT_IF(_p(132), _a(132) _LE_PP_FOR_133(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_133(_p, _a) LE_PP_BIT_IF(_p(133), _a(133) _LE_PP_FOR_134(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_134(_p, _a) LE_PP_BIT_IF(_p(134), _a(134) _LE_PP_FOR_135(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_135(_p, _a) LE_PP_BIT_IF(_p(135), _a(135) _LE_PP_FOR_136(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_136(_p, _a) LE_PP_BIT_IF(_p(136), _a(136) _LE_PP_FOR_137(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_137(_p, _a) LE_PP_BIT_IF(_p(137), _a(137) _LE_PP_FOR_138(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_138(_p, _a) LE_PP_BIT_IF(_p(138), _a(138) _LE_PP_FOR_139(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_139(_p, _a) LE_PP_BIT_IF(_p(139), _a(139) _LE_PP_FOR_140(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_140(_p, _a) LE_PP_BIT_IF(_p(140), _a(140) _LE_PP_FOR_141(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_141(_p, _a) LE_PP_BIT_IF(_p(141), _a(141) _LE_PP_FOR_142(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_142(_p, _a) LE_PP_BIT_IF(_p(142), _a(142) _LE_PP_FOR_143(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_143(_p, _a) LE_PP_BIT_IF(_p(143), _a(143) _LE_PP_FOR_144(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_144(_p, _a) LE_PP_BIT_IF(_p(144), _a(144) _LE_PP_FOR_145(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_145(_p, _a) LE_PP_BIT_IF(_p(145), _a(145) _LE_PP_FOR_146(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_146(_p, _a) LE_PP_BIT_IF(_p(146), _a(146) _LE_PP_FOR_147(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_147(_p, _a) LE_PP_BIT_IF(_p(147), _a(147) _LE_PP_FOR_148(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_148(_p, _a) LE_PP_BIT_IF(_p(148), _a(148) _LE_PP_FOR_149(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_149(_p, _a) LE_PP_BIT_IF(_p(149), _a(149) _LE_PP_FOR_150(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_150(_p, _a) LE_PP_BIT_IF(_p(150), _a(150) _LE_PP_FOR_151(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_151(_p, _a) LE_PP_BIT_IF(_p(151), _a(151) _LE_PP_FOR_152(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_152(_p, _a) LE_PP_BIT_IF(_p(152), _a(152) _LE_PP_FOR_153(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_153(_p, _a) LE_PP_BIT_IF(_p(153), _a(153) _LE_PP_FOR_154(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_154(_p, _a) LE_PP_BIT_IF(_p(154), _a(154) _LE_PP_FOR_155(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_155(_p, _a) LE_PP_BIT_IF(_p(155), _a(155) _LE_PP_FOR_156(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_156(_p, _a) LE_PP_BIT_IF(_p(156), _a(156) _LE_PP_FOR_157(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_157(_p, _a) LE_PP_BIT_IF(_p(157), _a(157) _LE_PP_FOR_158(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_158(_p, _a) LE_PP_BIT_IF(_p(158), _a(158) _LE_PP_FOR_159(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_159(_p, _a) LE_PP_BIT_IF(_p(159), _a(159) _LE_PP_FOR_160(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_160(_p, _a) LE_PP_BIT_IF(_p(160), _a(160) _LE_PP_FOR_161(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_161(_p, _a) LE_PP_BIT_IF(_p(161), _a(161) _LE_PP_FOR_162(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_162(_p, _a) LE_PP_BIT_IF(_p(162), _a(162) _LE_PP_FOR_163(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_163(_p, _a) LE_PP_BIT_IF(_p(163), _a(163) _LE_PP_FOR_164(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_164(_p, _a) LE_PP_BIT_IF(_p(164), _a(164) _LE_PP_FOR_165(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_165(_p, _a) LE_PP_BIT_IF(_p(165), _a(165) _LE_PP_FOR_166(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_166(_p, _a) LE_PP_BIT_IF(_p(166), _a(166) _LE_PP_FOR_167(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_167(_p, _a) LE_PP_BIT_IF(_p(167), _a(167) _LE_PP_FOR_168(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_168(_p, _a) LE_PP_BIT_IF(_p(168), _a(168) _LE_PP_FOR_169(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_169(_p, _a) LE_PP_BIT_IF(_p(169), _a(169) _LE_PP_FOR_170(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_170(_p, _a) LE_PP_BIT_IF(_p(170), _a(170) _LE_PP_FOR_171(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_171(_p, _a) LE_PP_BIT_IF(_p(171), _a(171) _LE_PP_FOR_172(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_172(_p, _a) LE_PP_BIT_IF(_p(172), _a(172) _LE_PP_FOR_173(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_173(_p, _a) LE_PP_BIT_IF(_p(173), _a(173) _LE_PP_FOR_174(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_174(_p, _a) LE_PP_BIT_IF(_p(174), _a(174) _LE_PP_FOR_175(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_175(_p, _a) LE_PP_BIT_IF(_p(175), _a(175) _LE_PP_FOR_176(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_176(_p, _a) LE_PP_BIT_IF(_p(176), _a(176) _LE_PP_FOR_177(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_177(_p, _a) LE_PP_BIT_IF(_p(177), _a(177) _LE_PP_FOR_178(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_178(_p, _a) LE_PP_BIT_IF(_p(178), _a(178) _LE_PP_FOR_179(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_179(_p, _a) LE_PP_BIT_IF(_p(179), _a(179) _LE_PP_FOR_180(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_180(_p, _a) LE_PP_BIT_IF(_p(180), _a(180) _LE_PP_FOR_181(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_181(_p, _a) LE_PP_BIT_IF(_p(181), _a(181) _LE_PP_FOR_182(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_182(_p, _a) LE_PP_BIT_IF(_p(182), _a(182) _LE_PP_FOR_183(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_183(_p, _a) LE_PP_BIT_IF(_p(183), _a(183) _LE_PP_FOR_184(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_184(_p, _a) LE_PP_BIT_IF(_p(184), _a(184) _LE_PP_FOR_185(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_185(_p, _a) LE_PP_BIT_IF(_p(185), _a(185) _LE_PP_FOR_186(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_186(_p, _a) LE_PP_BIT_IF(_p(186), _a(186) _LE_PP_FOR_187(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_187(_p, _a) LE_PP_BIT_IF(_p(187), _a(187) _LE_PP_FOR_188(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_188(_p, _a) LE_PP_BIT_IF(_p(188), _a(188) _LE_PP_FOR_189(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_189(_p, _a) LE_PP_BIT_IF(_p(189), _a(189) _LE_PP_FOR_190(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_190(_p, _a) LE_PP_BIT_IF(_p(190), _a(190) _LE_PP_FOR_191(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_191(_p, _a) LE_PP_BIT_IF(_p(191), _a(191) _LE_PP_FOR_192(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_192(_p, _a) LE_PP_BIT_IF(_p(192), _a(192) _LE_PP_FOR_193(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_193(_p, _a) LE_PP_BIT_IF(_p(193), _a(193) _LE_PP_FOR_194(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_194(_p, _a) LE_PP_BIT_IF(_p(194), _a(194) _LE_PP_FOR_195(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_195(_p, _a) LE_PP_BIT_IF(_p(195), _a(195) _LE_PP_FOR_196(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_196(_p, _a) LE_PP_BIT_IF(_p(196), _a(196) _LE_PP_FOR_197(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_197(_p, _a) LE_PP_BIT_IF(_p(197), _a(197) _LE_PP_FOR_198(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_198(_p, _a) LE_PP_BIT_IF(_p(198), _a(198) _LE_PP_FOR_199(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_199(_p, _a) LE_PP_BIT_IF(_p(199), _a(199) _LE_PP_FOR_200(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_200(_p, _a) LE_PP_BIT_IF(_p(200), _a(200) _LE_PP_FOR_201(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_201(_p, _a) LE_PP_BIT_IF(_p(201), _a(201) _LE_PP_FOR_202(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_202(_p, _a) LE_PP_BIT_IF(_p(202), _a(202) _LE_PP_FOR_203(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_203(_p, _a) LE_PP_BIT_IF(_p(203), _a(203) _LE_PP_FOR_204(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_204(_p, _a) LE_PP_BIT_IF(_p(204), _a(204) _LE_PP_FOR_205(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_205(_p, _a) LE_PP_BIT_IF(_p(205), _a(205) _LE_PP_FOR_206(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_206(_p, _a) LE_PP_BIT_IF(_p(206), _a(206) _LE_PP_FOR_207(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_207(_p, _a) LE_PP_BIT_IF(_p(207), _a(207) _LE_PP_FOR_208(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_208(_p, _a) LE_PP_BIT_IF(_p(208), _a(208) _LE_PP_FOR_209(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_209(_p, _a) LE_PP_BIT_IF(_p(209), _a(209) _LE_PP_FOR_210(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_210(_p, _a) LE_PP_BIT_IF(_p(210), _a(210) _LE_PP_FOR_211(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_211(_p, _a) LE_PP_BIT_IF(_p(211), _a(211) _LE_PP_FOR_212(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_212(_p, _a) LE_PP_BIT_IF(_p(212), _a(212) _LE_PP_FOR_213(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_213(_p, _a) LE_PP_BIT_IF(_p(213), _a(213) _LE_PP_FOR_214(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_214(_p, _a) LE_PP_BIT_IF(_p(214), _a(214) _LE_PP_FOR_215(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_215(_p, _a) LE_PP_BIT_IF(_p(215), _a(215) _LE_PP_FOR_216(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_216(_p, _a) LE_PP_BIT_IF(_p(216), _a(216) _LE_PP_FOR_217(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_217(_p, _a) LE_PP_BIT_IF(_p(217), _a(217) _LE_PP_FOR_218(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_218(_p, _a) LE_PP_BIT_IF(_p(218), _a(218) _LE_PP_FOR_219(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_219(_p, _a) LE_PP_BIT_IF(_p(219), _a(219) _LE_PP_FOR_220(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_220(_p, _a) LE_PP_BIT_IF(_p(220), _a(220) _LE_PP_FOR_221(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_221(_p, _a) LE_PP_BIT_IF(_p(221), _a(221) _LE_PP_FOR_222(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_222(_p, _a) LE_PP_BIT_IF(_p(222), _a(222) _LE_PP_FOR_223(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_223(_p, _a) LE_PP_BIT_IF(_p(223), _a(223) _LE_PP_FOR_224(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_224(_p, _a) LE_PP_BIT_IF(_p(224), _a(224) _LE_PP_FOR_225(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_225(_p, _a) LE_PP_BIT_IF(_p(225), _a(225) _LE_PP_FOR_226(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_226(_p, _a) LE_PP_BIT_IF(_p(226), _a(226) _LE_PP_FOR_227(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_227(_p, _a) LE_PP_BIT_IF(_p(227), _a(227) _LE_PP_FOR_228(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_228(_p, _a) LE_PP_BIT_IF(_p(228), _a(228) _LE_PP_FOR_229(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_229(_p, _a) LE_PP_BIT_IF(_p(229), _a(229) _LE_PP_FOR_230(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_230(_p, _a) LE_PP_BIT_IF(_p(230), _a(230) _LE_PP_FOR_231(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_231(_p, _a) LE_PP_BIT_IF(_p(231), _a(231) _LE_PP_FOR_232(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_232(_p, _a) LE_PP_BIT_IF(_p(232), _a(232) _LE_PP_FOR_233(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_233(_p, _a) LE_PP_BIT_IF(_p(233), _a(233) _LE_PP_FOR_234(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_234(_p, _a) LE_PP_BIT_IF(_p(234), _a(234) _LE_PP_FOR_235(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_235(_p, _a) LE_PP_BIT_IF(_p(235), _a(235) _LE_PP_FOR_236(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_236(_p, _a) LE_PP_BIT_IF(_p(236), _a(236) _LE_PP_FOR_237(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_237(_p, _a) LE_PP_BIT_IF(_p(237), _a(237) _LE_PP_FOR_238(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_238(_p, _a) LE_PP_BIT_IF(_p(238), _a(238) _LE_PP_FOR_239(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_239(_p, _a) LE_PP_BIT_IF(_p(239), _a(239) _LE_PP_FOR_240(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_240(_p, _a) LE_PP_BIT_IF(_p(240), _a(240) _LE_PP_FOR_241(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_241(_p, _a) LE_PP_BIT_IF(_p(241), _a(241) _LE_PP_FOR_242(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_242(_p, _a) LE_PP_BIT_IF(_p(242), _a(242) _LE_PP_FOR_243(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_243(_p, _a) LE_PP_BIT_IF(_p(243), _a(243) _LE_PP_FOR_244(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_244(_p, _a) LE_PP_BIT_IF(_p(244), _a(244) _LE_PP_FOR_245(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_245(_p, _a) LE_PP_BIT_IF(_p(245), _a(245) _LE_PP_FOR_246(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_246(_p, _a) LE_PP_BIT_IF(_p(246), _a(246) _LE_PP_FOR_247(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_247(_p, _a) LE_PP_BIT_IF(_p(247), _a(247) _LE_PP_FOR_248(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_248(_p, _a) LE_PP_BIT_IF(_p(248), _a(248) _LE_PP_FOR_249(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_249(_p, _a) LE_PP_BIT_IF(_p(249), _a(249) _LE_PP_FOR_250(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_250(_p, _a) LE_PP_BIT_IF(_p(250), _a(250) _LE_PP_FOR_251(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_251(_p, _a) LE_PP_BIT_IF(_p(251), _a(251) _LE_PP_FOR_252(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_252(_p, _a) LE_PP_BIT_IF(_p(252), _a(252) _LE_PP_FOR_253(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_253(_p, _a) LE_PP_BIT_IF(_p(253), _a(253) _LE_PP_FOR_254(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_254(_p, _a) LE_PP_BIT_IF(_p(254), _a(254) _LE_PP_FOR_255(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_255(_p, _a) LE_PP_BIT_IF(_p(255), _a(255) _LE_PP_FOR_256(_p, _a), _LE_PP_NOTHING)
#define _LE_PP_FOR_255(_p, _a) LE_PP_BIT_IF(_p(255), _a(255), _LE_PP_NOTHING)


#define LE_PP_FOR_LIMITATION 255

#endif // H_slPPfor_included