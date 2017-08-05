<?php
	include "connect.php";
	$b_no = $_GET['building_no'];

	echo "b_no = $b_no";
	
	$q = "SELECT toilet_no,toilet_name,rating,numof_review FROM toilet WHERE building_no = $b_no ORDER BY numof_review DESC";
	$res = mysql_query($q,$connect);	

	while($row = mysql_fetch_array($res)) {
		$q2 = "SELECT review_no, content, thumb, nickname FROM review JOIN member WHERE review.member_no = member.member_no and toilet_no = $row[toilet_no] ORDER BY  numof_rcmd,wdate DESC LIMIT $row[numof_review]";
		$res2 = mysql_query($q2,$connect);

		//이미지 찾기 
		$img_src = "abc";
		while($row2 = mysql_fetch_array($res2)){
			if($img_src == 'abc' && strlen($row2['thumb']) > 3){
				$img_src = $row2['thumb'];
			}
		}
		if($img_src == 'abc') {
			$img_src = "default_thumb.jpg";
		}
		mysql_data_seek($res2,0);

		echo '<div id="cont">';
		echo '<div class="row"> <div class="col-xs-12"> <p>'.$row['toilet_name'].'</p> </div></div>';
		echo '<div class="row"><div class="col-xs-6"> <img src="'.$img_src.'" /> </div>';
		
		if($row['numof_review'] == 1) {
			$row2 = mysql_fetch_array($res2);
			$cont;
			if (strlen($row2['content'])>58) {
				$cont = mb_substr($row2['content'],0,20,"UTF-8")."......";
			}
			else{
				$cont = $row2['content'];
			}
			echo '<div class="col-xs-6">'.$row2['nickname'].'</div><a href="post.php?review_no='.$row2['review_no'].'"><div class="col-xs-6">'.$cont.'</div></a><div class = "col-xs-6"><br></div>';
			echo '<div class="col-xs-6">*******</div><div class="col-xs-6">+_+_+_+ +_+_+_+ +_+_+_+</div><div class = "col-xs-6"><br></div></div>';
		}
		else {
			$row2 = mysql_fetch_array($res2);
			$cont;
			if (strlen($row2['content'])>58) {
				$cont = mb_substr($row2['content'],0,20,"UTF-8")."......";
			}
			else{
				$cont = $row2['content'];
			}
			echo '<div class="col-xs-6">'.$row2['nickname'].'</div><a href="post.php?review_no='.$row2['review_no'].'"><div class="col-xs-6">'.$cont.'</div></a><div class = "col-xs-6"><br></div>';

			$row2 = mysql_fetch_array($res2);
			if (strlen($row2['content'])>58) {
				$cont = mb_substr($row2['content'],0,20,"UTF-8")."......";
			}
			else{
				$cont = $row2['content'];
			}
			echo '<div class="col-xs-6">'.$row2['nickname'].'</div><a href="post.php?review_no='.$row2['review_no'].'"><div class="col-xs-6">'.$cont.'</div></a><div class = "col-xs-6"><br></div></div>';
		}
		$rate = round($row['rating'] / $row['numof_review'],2);
		echo '<div class="row"><div class="col-xs-6"> 평점 : '.$rate.'</div>';
		echo '<div class="col-xs-6"><a href="toilet_board.php?toilet_no='.$row['toilet_no'].'">게시글 더보기</a></div></div>';
	}
	echo '<div class="row"><div class="col-xs-3"></div><div class="col-xs-6"><a id="tin" href="create_review.php?part=2&building_no='.$b_no.'">화장실추가</a> </div><div class="col-xs-3"></div></div></div>';

?>
