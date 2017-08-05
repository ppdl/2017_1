
		function moveMap() {
		   if(navigator.geolocation) {
			navigator.geolocation.getCurrentPosition(success, fail);
		} else {
			document.getElementById('map').textContent = "지원X";
		}
	   };
	   function success(location) {
		   
			var mapContainer = document.getElementById('map'), // 지도를 표시할 div 
				mapOption = { 
					center: new daum.maps.LatLng(location.coords.latitude, location.coords.longitude), // 지도의 중심좌표
					level: 3 // 지도의 확대 레벨
				};
			var map = new daum.maps.Map(mapContainer, mapOption); // 지도를 생성합니다
			
			var position2 = new daum.maps.LatLng(location.coords.latitude, location.coords.longitude);
			var imageSrc = 'img/loc2.png', // 마커이미지의 주소입니다    
			imageSize = new daum.maps.Size(26, 45), // 마커이미지의 크기입니다
			imageOption = {offset: new daum.maps.Point(13, 45)}; // 마커이미지의 옵션입니다. 마커의 좌표와 일치시킬 이미지 안에서의 좌표를 설정합니다.
			
			// 마커의 이미지정보를 가지고 있는 마커이미지를 생성합니다
			var markerImage = new daum.maps.MarkerImage(imageSrc, imageSize, imageOption);
			
			var marker2 = new daum.maps.Marker({ // 현재 위치를 나타낼 마커 생성
				position: position2,
				image: markerImage, // 마커이미지 설정 
				clickable: true // 마커를 클릭했을 때 지도의 클릭 이벤트(기본 설정: 아무 일도 일어나지 않는 것)가 발생하지 않도록 설정합니다
			});
			marker2.setMap(map);
		}
	
		function fail() {
			document.getElementById('map').textContent = "못 찾음";
		}
	   var elGPS = document.getElementById('gps');
	   elGPS.addEventListener('click', moveMap, false);
	   
	   function makeMap(coords) {
			var mapContainer = document.getElementById('map'), // 지도를 표시할 div 
				mapOption = { 
					center: coords, // 지도의 중심좌표
					level: 3 // 지도의 확대 레벨
				};
			var map = new daum.maps.Map(mapContainer, mapOption); // 지도를 생성합니다.
	   }