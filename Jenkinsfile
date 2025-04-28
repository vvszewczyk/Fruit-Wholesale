pipeline
{
    agent any
	
	environment 
	{
		DEPLOY_TAG = "v1.0.${env.BUILD_NUMBER}"
		IMAGE_NAME = "vvszewczyk/fruit_deploy"
	}
	
    stages
    {
        stage('Build')
        {
            steps
            {
                echo "Building project in container..."
                sh '''docker build -t my_builder_image -f Dockerfile.build .'''
            }
        }
        stage('Test') 
        {
            steps 
            {
                echo "Running tests..."
                script 
                {
                    def output = sh(script: "docker run --name my_test_run --rm my_builder_image ./fruit_test", returnStdout: true)
                    echo "Captured test output:\n${output}"
                    writeFile file: "test_output.log", text: output
                }
            }
        }
        stage('Archive logs') 
        {
            steps 
            {
                echo "Archiving logs..."
                archiveArtifacts artifacts: 'test_output.log', fingerprint: true
            }
        }
		stage('Deploy')
		{
			steps
			{
				echo "Building deploy image..."
				sh '''docker build --build-arg BUILDER_IMAGE=my_builder_image -t ${IMAGE_NAME}:${DEPLOY_TAG} -f Dockerfile.deploy .'''
			}
		}
		stage('Push to registry') 
		{
			steps 
			{
				withCredentials([usernamePassword(credentialsId: 'docker-hub-creds', usernameVariable: 'DOCKER_USER', passwordVariable: 'DOCKER_PASS')]) 
				{
					sh '''
					echo "$DOCKER_PASS" | docker login -u "$DOCKER_USER" --password-stdin
					docker push ${IMAGE_NAME}:${DEPLOY_TAG}
					'''
				}
			}
		}
		stage('Smoke Test') 
		{
			steps 
			{
				echo "Running smoke tests against deploy image..."
				sh '''docker run --rm ${IMAGE_NAME}:${DEPLOY_TAG} ./fruit_test --gtest_filter=SmokeTest.*'''
			}
		}
        stage('Check Custom Jenkins') 
        {
            steps 
            {
                echo "Verifying custom Jenkins image..."
                sh "docker --version"
            }
        }
    }
	
	post 
	{
		success 
		{
			echo "Pipeline completed successfully – deploy image: ${IMAGE_NAME}:${DEPLOY_TAG}"
		}
		failure 
		{
		  echo "Pipeline failed – check logs"
		}
	}
}
