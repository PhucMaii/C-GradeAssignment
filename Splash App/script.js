const APIKEY = "WKOCIdgBGr0MBKKAd0wZ1-2HT7LWWLqGpVx8msmzdlU";

// Path Parameters
// http://facebook.com/prabh/profile/user




// Query Parameters ( where you pass data in key-value pair)
// http://facebook.com?user=prabh&type=profile&value=user


// When you are using AXIOS, you don't have to convert the promise result to JSON
// becauseit's already done for you by AXIOS

// just like fetch, Axios is also a htttp client to communicate with the server
let imagesData;
const fetchesImages = async () => {
    try {
        return await axios.get(`https://api.unsplash.com/photos/?client_id=${APIKEY}`);
    } catch(error) {
        alert("There was an error ", error);
    }
}

const fetchImagesByKeyword = async () => {
    const searchKeyword = document.getElementById('search-keyword');
    try {
        return await axios.get(`https://api.unsplash.com/search/photos/?query=${searchKeyword.value}&client_id=${APIKEY}`);
        
    } catch(error) {
        alert("There was an error ", error);
    }
}

const generateUI = (arrayOfImages) => {
    let photoSection = document.getElementById('photo-section')
    photoSection.innerHTML = "";
    arrayOfImages.forEach((imageObject) => {

        let imageContainer = document.createElement('div');


        imageContainer.innerHTML = `
        <img src=${imageObject.url}>
        <time>Created At: ${modifyDate(imageObject.createdAt)}</time>
        <p>${imageObject.description}</p>
        `



        photoSection.appendChild(imageContainer);


    })
}


function modifyDate(date) {
    let d = new Date(date);
    // let readableDate = `${d.getDate()}/${d.getMonth()}/${d.getFullYear()}`;
    return d.toLocaleDateString();

}

async function getImageDataByKeyword() {
    const { data } = await fetchImagesByKeyword();

    imagesData = data.results.map((imageObject) => {
        return {
            url:imageObject.urls.full,
            createdAt: imageObject.created_at,
            likes: imageObject.likes,
            description: imageObject.description || "Random Description"
        }
    });
    generateUI(imagesData);
    
}

async function getData() {
    const { data } = await fetchesImages();
    console.log(data,"Original Data");
    imagesData = data.map((imageObject) => {
        return {
            url:imageObject.urls.full,
            createdAt: imageObject.created_at,
            likes: imageObject.likes,
            description: imageObject.description || "Random Description"
        }
    });
    generateUI(imagesData);
}

getData();