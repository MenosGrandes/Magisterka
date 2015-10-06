var container, stats;
var camera, scene, renderer;
init();
animate();
function radToDegree(angle) {
	return angle * Math.PI / 180.0;
}

var mydata;
function initGUI() {
	var gui = new dat.GUI({
			height : 5 * 32 - 1
		});
	var ff = gui.addFolder("L-Systems JSON");
	for (var i = 0; i < mydata.length; i++) {

		var f = ff.addFolder(mydata[i].name);

		f.add(mydata[i], 'start');
		f.add(mydata[i], 'iterations').min(0).max(100).step(1);
		f.add(mydata[i], 'angle').min(0).max(360).step(0.1);

	}

}

function initLSystem(Lsystem) {
	console.log(mydata[Lsystem].name);
	var rules = mydata[Lsystem].rules;
	var tempString = "";
	var resault = mydata[Lsystem].start;
	for (j = 0; j < mydata[Lsystem].iterations; j++) {
		for (var i = 0; i < resault.length; i++) {
			var found = false;
			var compareString = resault[i];
			for (var g = 0; g < rules.length; g++) {
				if (rules[g].from == compareString) {
					tempString += rules[g].listProbability[0].to;
					found = true;
				}
			}
			if (!found) {
				tempString += compareString;
			}
		}
		resault = tempString;
		tempString = "";
			console.log("ITER: "+j);
	console.log(resault);
	}

	return resault;
}

function drawLSystem(resault, angle, vertices) {

	var current = {
		pos : new THREE.Vector3(0, 0, 0),
		rot : new THREE.Vector3(0, 1, 0)
	};
	
		var stack = [];
	vertices.push(current.pos);
	for (var i = 0; i < resault.length; i++) {
		switch (resault[i]) {
		case "F":
			current.pos = new THREE.Vector3(current.pos.x + 5 * current.rot.x, current.pos.y + 5 * current.rot.y, current.pos.z + 5 * current.rot.z);
			vertices.push(current.pos);
			if (resault[i + 1] != ']') {
				vertices.push(current.pos);
			}
			break;
		case "+":
			var temp = new THREE.Vector3(current.rot.x * Math.cos(radToDegree(-angle)) - current.rot.y * Math.sin(radToDegree(-angle)), current.rot.x * Math.sin(radToDegree(-angle)) + current.rot.y * Math.cos(radToDegree(-angle)), current.rot.z);
			current.rot = temp;
			break;
		case "-":
			var temp = new THREE.Vector3(current.rot.x * Math.cos(radToDegree(angle)) - current.rot.y * Math.sin(radToDegree(angle)), current.rot.x * Math.sin(radToDegree(-angle)) + current.rot.y * Math.cos(radToDegree(angle)), current.rot.z);
			current.rot = temp;
			break;
		case "[":
			//stack.push(current);
			break;
		case "]":
			//current = stack.pop();
			//vertices.push(current.pos);

			break;
		}
	}
}
function addLSystem(LSystem)
{
	
		/*LSYSTEM*/
	var geometry2 = new THREE.Geometry();
	var material2 = new THREE.LineBasicMaterial({
			color : 0x292900,
			opacity : 1
		});

	drawLSystem(initLSystem(LSystem), 72, geometry2.vertices);
		var lines2 = new THREE.LineSegments(geometry2, material2);
	scene.add(lines2)
	
}
function init() {
	
	/*READ JSON*/
	mydata = JSON.parse(dupa);
	/*ELSE*/
	container = document.createElement('div');
	document.body.appendChild(container);
	var info = document.createElement('div');
	info.style.position = 'absolute';
	info.style.top = '10px';
	info.style.width = '100%';
	info.style.textAlign = 'center';
	info.innerHTML = '<a href="http://threejs.org" target="_blank">three.js</a> - orthographic view';
	container.appendChild(info);
	camera = new THREE.OrthographicCamera(window.innerWidth / -2, window.innerWidth / 2, window.innerHeight / 2, window.innerHeight / -2, -500, 1000);
	camera.position.x = 200;
	camera.position.y = 100;
	camera.position.z = 200;
	scene = new THREE.Scene();
	/*GRID*/
	var size = 500,
	step = 50;

	var gridHelper = new THREE.GridHelper(size, step);
	scene.add(gridHelper);
addLSystem(2);
	/*GUI*/
	initGUI();

	
	renderer = new THREE.CanvasRenderer();
	renderer.setClearColor(0xf0f0f0);
	renderer.setPixelRatio(window.devicePixelRatio);
	renderer.setSize(window.innerWidth, window.innerHeight);
	container.appendChild(renderer.domElement);
	stats = new Stats();
	stats.domElement.style.position = 'absolute';
	stats.domElement.style.top = '0px';
	container.appendChild(stats.domElement);
	window.addEventListener('resize', onWindowResize, false);

}
function onWindowResize() {
	camera.left = window.innerWidth / -2;
	camera.right = window.innerWidth / 2;
	camera.top = window.innerHeight / 2;
	camera.bottom = window.innerHeight / -2;
	camera.updateProjectionMatrix();
	renderer.setSize(window.innerWidth, window.innerHeight);
}
function animate() {
	requestAnimationFrame(animate);
	render();
	stats.update();
}
function render() {
	var timer = Date.now() * 0.0001;
	camera.position.x = Math.cos(timer) * 200;
	camera.position.z = Math.sin(timer) * 200;
	camera.lookAt(scene.position);
	renderer.render(scene, camera);
}
